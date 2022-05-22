/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:22:34 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:23:07 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_command_list(t_command *command)
{
	t_command	*tmp;

	while (command)
	{
		tmp = command;
		command = command->next;
		free(tmp->cmd_args);
		free(tmp);
	}
	free(command);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(env);
}

void	free_parser(char *line, char **token_arr, t_command *command)
{
	free(line);
	free_command_list(command);
	free_arr(token_arr);
}
