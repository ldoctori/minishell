/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:12:43 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 18:12:45 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_all_pid(int **exit_status_fd, int *pid, int cmd_number)
{
	int	j;

	j = 0;
	while (j < cmd_number)
	{
		waitpid(pid[j], &(g_last_exit.exit_status), 0);
		if (g_last_exit.exit_status == 9)
			g_last_exit.exit_status = 130;
		if (j < cmd_number - 1)
			write(exit_status_fd[j][1],
				&(g_last_exit.exit_status), sizeof(int));
		j++;
	}
	g_last_exit.flag = -1;
}

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
	wait_all_pid(exit_status_fd, pid, cmd_number);
	j = 0;
	while (j < cmd_number - 1)
	{
		close(exit_status_fd[j][0]);
		close(exit_status_fd[j][1]);
		j++;
	}
}
