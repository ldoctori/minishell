/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:10:54 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 09:40:44 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_path(char **paths, t_command *command)
{
	char	*valid_path;
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", command->cmd_args[0]);
	while (paths && paths[i])
	{
		valid_path = ft_strjoin(paths[i], cmd);
		if (access(valid_path, X_OK) == 0)
		{
			free(cmd);
			return (valid_path);
		}
		free(valid_path);
		i++;
	}
	cmd_error(cmd);
	return (0);
}

char	*is_exit_status_read(t_command *command, int **exit_status_fd, int i)
{
	int		j;
	int		exit_status_int;
	char	*exit_status;

	if (i == 0)
		return (NULL);
	j = 0;
	exit_status = NULL;
	while (command->cmd_args[j])
	{
		if (ft_strcmp(command->cmd_args[j], "$?") == 0)
		{
			read(exit_status_fd[i - 1][0], &exit_status_int, sizeof(int));
			exit_status = ft_itoa(exit_status_int);
			command->cmd_args[j] = exit_status;
			break ;
		}
		j++;
	}
	return (exit_status);
}

void	exec_pid(t_command *command, int *exp_fd, int **exit_status_fd, int i)
{
	char	*str_of_paths;
	char	**paths;
	char	*valid_path;
	char	*exit_status;

	exit_status = is_exit_status_read(command, exit_status_fd, i);
	if (access(command->cmd_args[0], X_OK) == 0)
	{
		execve(command->cmd_args[0], command->cmd_args, command->envp);
		return ;
	}
	if (is_builtin(command, exp_fd) == 1)
		exit(EXIT_SUCCESS);
	str_of_paths = get_path_env(command->envp);
	paths = ft_split(str_of_paths, ':');
	valid_path = find_cmd_path(paths, command);
	execve(valid_path, command->cmd_args, command->envp);
	free(valid_path);
	free_arr(paths);
	free(str_of_paths);
}

t_command	*cmds_executer_helper(t_command *command,
									int *exp_fd, int *pid, int *i)
{
	del_fd_free(command->del_fd);
	close(exp_fd[1]);
	if ((ft_strcmp(command->cmd_args[0], "export") == 0
			|| ft_strcmp(command->cmd_args[0], "unset") == 0)
		&& command->cmd_args[1] != NULL)
	{
		waitpid(pid[*i], NULL, WNOHANG);
		set_new_env_list(command, exp_fd);
	}
	close(exp_fd[0]);
	free(exp_fd);
	(*i)++;
	command = command->next;
	return (command);
}

void	cmds_executer(t_command *command, char *envp[])
{
	int	*pid;
	int	i;
	int	**fd;
	int	*exp_fd;
	int	**exit_status_fd;

	pid = malloc(sizeof(int) * command->cmd_number);
	fd = fd_allocate(command->cmd_number);
	exit_status_fd = fd_allocate(command->cmd_number);
	i = 0;
	while (command)
	{
		here_doc(command);
		exp_fd = malloc(sizeof(int) * 2);
		pipe(exp_fd);
		pid[i] = fork();
		if (pid_error(pid, i, fd, command->cmd_number) && pid[i] == 0)
		{
			close(exp_fd[0]);
			fd_duplicate(fd, i, command);
			exec_pid(command, exp_fd, exit_status_fd, i);
		}
		command = cmds_executer_helper(command, exp_fd, pid, &i);
	}
	finish_exec(fd, exit_status_fd, pid, i);
}
