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

void	wait_all_pid(int *pid, int cmd_number)
{
	int	j;

	j = 0;
	while (j < cmd_number)
	{
		waitpid(pid[j], &(g_last_exit.exit_status), 0);
		if (g_last_exit.exit_status == 9)
			g_last_exit.exit_status = 130;
		else if (g_last_exit.exit_status != 131)
			g_last_exit.exit_status = g_last_exit.exit_status >> 8;
		j++;
	}
	g_last_exit.flag = -1;
}

void	close_wait(int **fd, int *pid, int cmd_number)
{
	int	j;

	j = 0;
	while (j < cmd_number - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	wait_all_pid(pid, cmd_number);
}
