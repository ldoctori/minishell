/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_for_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:53:17 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:53:36 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_user(char **envp)
{
	int		i;
	char	*user;

	i = 0;
	user = NULL;
	while (envp[i])
	{
		if (ft_strncmp("USER=", envp[i], 5) == 0)
		{
			user = envp[i] + 5;
			break ;
		}
		i++;
	}
	user = ft_strjoin(user, ":");
	return (user);
}

char	*cut_path(char *path)
{
	char	*small_path;
	char	*tmp;
	int		i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	tmp = ft_strdup(path + i + 1);
	small_path = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (small_path);
}

char	*path_for_prompt(char **envp)
{
	char	cwd_path[256];
	char	*small_path;
	char	*promt;
	char	*user;

	if (getcwd(cwd_path, 256) == 0)
	{
		perror("cannot write current working directiry path");
		return (NULL);
	}
	small_path = cut_path(cwd_path);
	user = get_user(envp);
	promt = ft_strjoin(user, small_path);
	free(user);
	free(small_path);
	return (promt);
}
