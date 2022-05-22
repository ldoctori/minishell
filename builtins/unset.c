/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:01:39 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 13:01:52 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_command *cmd, int *exp_fd)
{
	int	i;

	i = 1;
	while (cmd->env)
	{
		i = 1;
		while (cmd->cmd_args[i])
		{
			if (ft_strcmp(cmd->env->name, cmd->cmd_args[i]) != 0)
			{
				write(exp_fd[1], cmd->env->name, ft_strlen(cmd->env->name));
				write(exp_fd[1], "=", 1);
				write(exp_fd[1], cmd->env->value, ft_strlen(cmd->env->value));
			}
			i++;
		}
		write(exp_fd[1], "\n", 1);
		cmd->env = cmd->env->next;
	}
}
