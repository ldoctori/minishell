/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:10:54 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 18:12:27 by ldoctori         ###   ########.fr       */
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

	g_last_exit.flag = 0;
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

int	*fork_create(int i)
{
	int	*exp_fd;

	exp_fd = malloc(sizeof(int) * 2);
	pipe(exp_fd);
	g_last_exit.pid[i] = fork();
	g_last_exit.flag = g_last_exit.pid[i];
	return (exp_fd);
}

void	cmds_executer(t_command *command, char *envp[])
{
	int	i;
	int	**fd;
	int	*exp_fd;
	int	**exit_status_fd;

	fd = fd_allocate(command->cmd_number);
	exit_status_fd = fd_allocate(command->cmd_number);
	i = 0;
	while (command)
	{
		exp_fd = fork_create(i);
		if (pid_error(g_last_exit.pid, i, fd, command->cmd_number)
			&& g_last_exit.pid[i] == 0)
		{	
			signal(SIGINT, SIG_IGN);
			here_doc(command);
			signal(SIGQUIT, SIG_DFL);
			close(exp_fd[0]);
			fd_duplicate(fd, i, command);
			exec_pid(command, exp_fd, exit_status_fd, i);
		}
		command = cmds_executer_helper(command, exp_fd, g_last_exit.pid, &i);
	}
	finish_exec(fd, exit_status_fd, g_last_exit.pid, i);
}
