/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:04:51 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 16:27:06 by cadda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_file_error(int in_fd, int out_fd, t_command *command)
{
	if (in_fd < 0)
	{
		perror(command->infile);
		exit(EXIT_FAILURE);
	}
	if (out_fd < 0)
	{
		perror(command->outfile);
		exit(EXIT_FAILURE);
	}
}

void	pipe_error(int pipe)
{
	if (pipe < 0)
	{
		perror("cannot create pipe");
		exit(EXIT_FAILURE);
	}
}

void	cmd_error(char *cmd)
{
	printf("%s: command not found\n", (cmd + 1));
	free(cmd);
	exit(EXIT_FAILURE);
}

int	pid_error(int *pid, int i, int **fd, int cmd_number)
{
	if (pid[i] < 0)
	{
		perror("cannot create child process");
		free(pid);
		free_fd(fd, cmd_number - 1);
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	here_doc_error(char *line, char *delimiter)
{
	if (!line)
	{
		printf("minishell: warning: here-document "
			"delimited by end-of-line (wanted '%s')\n", delimiter);
		return ;
	}
	free(line);
}
