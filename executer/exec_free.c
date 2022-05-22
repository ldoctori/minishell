/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:18:56 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:19:12 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_fd_free(int *del_fd)
{
	if (del_fd == NULL)
		return ;
	close(del_fd[0]);
	close(del_fd[1]);
	free(del_fd);
}

void	free_fd(int **fd, int fd_number)
{
	int	i;

	i = 0;
	while (i < fd_number)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
