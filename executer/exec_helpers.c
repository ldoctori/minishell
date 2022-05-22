/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:13:05 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:13:06 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_wait(int **fd, int **exit_status_fd, int *pid, int cmd_number)
{
	int	j;

	j = 0;
	while (j < cmd_number - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	j = 0;
	while (j < cmd_number)
	{
		waitpid(pid[j], &g_last_exit_status, 0);
		if (j < cmd_number - 1)
			write(exit_status_fd[j][1], &g_last_exit_status, sizeof(int));
		j++;
	}
	j = 0;
	while (j < cmd_number - 1)
	{
		close(exit_status_fd[j][0]);
		close(exit_status_fd[j][1]);
		j++;
	}
}

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
