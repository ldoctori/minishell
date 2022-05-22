/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:31:54 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 14:31:56 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_envp_arr(char **envp)
{
	char	**new_envp;
	int		size;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (envp[size])
	{
		new_envp[size] = ft_strldup(envp[size], ft_strlen(envp[size]) + 1);
		size++;
	}
	new_envp[size] = NULL;
	return (new_envp);
}

int	get_env_number(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

char	**updape_envp_arr(t_env *env, char **envp)
{
	char	*tmp;
	int		size;

	if (envp)
		free_arr(envp);
	size = get_env_number(env);
	envp = malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		envp[size] = ft_strjoin(tmp, env->value);
		free(tmp);
		size++;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
}
