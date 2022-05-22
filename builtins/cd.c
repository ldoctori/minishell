/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:16:04 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 16:51:44 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_command *command)
{
	char	tmp[256];
	char	*old_pwd;
	char	*pwd;

	getcwd(tmp, 256);
	old_pwd = ft_strdup(tmp);
	chdir(command->cmd_args[1]);
	getcwd(tmp, 256);
	pwd = ft_strdup(tmp);
	while (command->env)
	{
		if (ft_strcmp(command->env->name, "OLDPWD") == 0)
		{
			free(command->env->value);
			command->env->value = old_pwd;
		}
		else if (ft_strcmp(command->env->name, "PWD") == 0)
		{
			free(command->env->value);
			command->env->value = pwd;
		}
		command->env = command->env->next;
	}
}
