/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:44:29 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:49:58 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_env(char *envp)
{
	t_env	*env;
	char	*eq;
	int		len;

	eq = ft_strchr(envp, '=');
	if (eq)
		len = ft_strchr(envp, '=') - envp;
	else
		len = ft_strlen(envp);
	env = malloc(sizeof(t_env));
	env->name = ft_strldup(envp, len);
	if (eq)
		env->value = ft_strdup(eq + 1);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

t_env	*get_env_list(char **envp)
{
	t_env	*env;
	t_env	*start;
	int		i;

	if (envp == NULL || *envp == NULL)
		return (NULL);
	env = get_env(envp[0]);
	start = env;
	env->next = NULL;
	i = 1;
	while (envp[i])
	{
		env->next = get_env(envp[i]);
		env = env->next;
		i++;
	}
	return (start);
}

void	set_new_env_list_helper(t_command *cmd, char *final)
{
	t_env	*new_env_list;
	char	**new_env;

	new_env = ft_split(final, '\n');
	free(final);
	new_env_list = get_env_list(new_env);
	free_arr(new_env);
	free_env_list(cmd->env);
	while (cmd)
	{
		cmd->env = new_env_list;
		cmd = cmd->next;
	}
}

void	set_new_env_list(t_command *cmd, int *exp_fd)
{
	char	*tmp;
	char	*line;
	char	*final;

	line = get_next_line(exp_fd[0]);
	final = malloc(1);
	final[0] = '\0';
	while (line != NULL)
	{
		tmp = final;
		final = ft_strjoin(final, line);
		free(tmp);
		free(line);
		line = get_next_line(exp_fd[0]);
	}
	free(line);
	set_new_env_list_helper(cmd, final);
}
