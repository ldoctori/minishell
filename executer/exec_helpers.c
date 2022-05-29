/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:13:05 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 16:27:44 by cadda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	finish_exec(int **fd, int **exit_status_fd, int *pid, int cmd_number)
{
	close_wait(fd, exit_status_fd, pid, cmd_number);
	free(pid);
	free_fd(fd, cmd_number - 1);
	free_fd(exit_status_fd, cmd_number - 1);
}

int	**fd_allocate(int cmd_number)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (cmd_number - 1));
	i = 0;
	while (i < cmd_number - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe_error(pipe(fd[i]));
		i++;
	}
	return (fd);
}

void	set_cmd_number(t_command *command)
{
	int			n;
	t_command	*tmp;

	n = 0;
	tmp = command;
	while (command != NULL)
	{
		command = command->next;
		n++;
	}
	while (tmp)
	{
		tmp->cmd_number = n;
		tmp = tmp->next;
	}
}

char	*get_path_env(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}

t_command	*cmds_executer_helper(t_command *command,
									int *exp_fd, int *pid, int *i)
{
	if (ft_strcmp(command->cmd_args[0], "./minishell") == 0)
			g_last_exit.flag = -2;
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
