/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:17:19 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:17:21 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_file_path(char *file, char **envp)
{
	int		i;
	char	*file_path;

	i = 0;
	file = ft_strjoin("/", file);
	file_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PWD=", envp[i], 4) == 0)
		{
			file_path = envp[i] + 4;
			break ;
		}
		i++;
	}
	if (!file_path)
		return (0);
	file_path = ft_strjoin(file_path, file);
	free(file);
	return (file_path);
}

int	open_file_fd(char *file, t_command *command, char c)
{
	int		file_fd;
	char	*file_path;

	file_path = find_file_path(file, command->envp);
	if (c == 'i' && access(file_path, R_OK) != 0)
	{
		free(file_path);
		return (-1);
	}
	if (command->append_out == 1)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (c == 'o' && command->append_out != 1)
		file_fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(file_path, O_RDONLY);
	free(file_path);
	return (file_fd);
}
