/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:16:31 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:16:55 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(t_command *command)
{
	char	*line;
	char	*final;
	char	*tmp;

	if (command->delimiter == NULL)
		return ;
	command->del_fd = malloc(sizeof(int) * 2);
	line = get_next_line(STDIN_FILENO);
	final = malloc(1);
	final[0] = '\0';
	while (line != NULL && ft_strncmp(command->delimiter,
			line, ft_strlen(line) - 1) != 0)
	{
		tmp = final;
		final = ft_strjoin(final, line);
		free(tmp);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	pipe(command->del_fd);
	write(command->del_fd[1], final, ft_strlen(final));
	free(final);
	return ;
}
