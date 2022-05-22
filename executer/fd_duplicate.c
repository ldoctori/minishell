/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_duplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:15:09 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:15:13 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	some_fd_close(int **fd, int cmd_number, int *del_fd)
{
	int	j;

	j = 0;
	while (j < cmd_number - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	if (del_fd != NULL)
	{
		close(del_fd[0]);
		close(del_fd[1]);
	}
}

void	fd_duplicate(int **fd, int i, t_command *command)
{
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (command->cmd_number > 1 && i > 0)
		in_fd = fd[i - 1][0];
	if (command->cmd_number > 1 && i < command->cmd_number - 1)
		out_fd = fd[i][1];
	if (command->del_fd != NULL)
		in_fd = command->del_fd[0];
	if (command->infile != NULL)
		in_fd = open_file_fd(command->infile, command, 'i');
	if (command->outfile != NULL)
		out_fd = open_file_fd(command->outfile, command, 'o');
	open_file_error(in_fd, out_fd, command);
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	some_fd_close(fd, command->cmd_number, command->del_fd);
}
