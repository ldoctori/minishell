/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:46:43 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 14:32:35 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollar_from_env(t_command *command, char *token)
{
	t_env	*env;
	char	*dollar;

	env = command->env;
	dollar = NULL;
	if (*(token + 1) == '?')
		return (ft_itoa(g_last_exit.exit_status));
	while (env)
	{
		if (ft_strcmp(token + 1, env->name) == 0)
		{
			dollar = ft_strdup(env->value);
			return (dollar);
		}
		env = env->next;
	}
	dollar = malloc(2);
	dollar[0] = '\0';
	return (dollar);
}

char	*dollar_end(char *dollar)
{
	int	i;

	i = 1;
	while ((dollar[i] >= 'A' && dollar[i] <= 'Z')
		|| (dollar[i] >= 'a' && dollar[i] <= 'z')
		|| (dollar[i] >= '0' && dollar[i] <= '9')
		|| (dollar[i] == '?' && i < 2))
			i++;
	return (dollar + i);
}

char	*double_quot_helper(t_command *command, char *token, char *dollar)
{
	char	*dq_str;
	char	*tmp;
	char	*end;

	dq_str = ft_strldup(token, dollar - token);
	end = dollar_end(dollar);
	dollar = ft_strldup(dollar, end - dollar);
	tmp = dollar;
	dollar = dollar_from_env(command, dollar);
	free(tmp);
	if (!dollar)
		return (NULL);
	tmp = dq_str;
	dq_str = ft_strjoin(dq_str, dollar);
	free(tmp);
	free(dollar);
	tmp = dq_str;
	end = ft_strldup(end, ft_strlen(end));
	dq_str = ft_strjoin(dq_str, end);
	free(tmp);
	free(end);
	return (dq_str);
}

void	*double_quot_arg(t_command *command, char *token)
{
	char	*dq_str;
	char	*tmp;
	char	*dollar;

	dq_str = ft_strldup(token + 1, ft_strlen(token + 1) - 1);
	dollar = ft_strchr(dq_str, '$');
	while (dollar)
	{
		tmp = dq_str;
		dq_str = double_quot_helper(command, dq_str, dollar);
		free(tmp);
		dollar = ft_strchr(dq_str, '$');
	}
	return (dq_str);
}

void	set_cmd_args(t_command *command, char **token_arr, int i, int j)
{
	char	*new_arg;

	new_arg = NULL;
	if (token_arr[j][0] == '$')
		new_arg = dollar_from_env(command, token_arr[j]);
	if (token_arr[j][0] == 39)
		new_arg = ft_strldup(token_arr[j] + 1, ft_strlen(token_arr[j] + 1) - 1);
	if (token_arr[j][0] == '"')
		new_arg = double_quot_arg(command, token_arr[j]);
	if (new_arg)
	{
		free(token_arr[j]);
		token_arr[j] = new_arg;
	}
	command->cmd_args[i] = token_arr[j];
}
