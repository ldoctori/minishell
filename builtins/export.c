/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:27:33 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 12:27:35 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_cmd_args(t_command *cmd, int *exp_fd, int change)
{
	int		i;
	char	*eq;

	i = change + 1;
	while (cmd->cmd_args[i])
	{
		eq = ft_strchr(cmd->cmd_args[i], '=');
		eq = NULL;
		if (!eq)
		{
			write(exp_fd[1], cmd->cmd_args[i], ft_strlen(cmd->cmd_args[i]));
			write(exp_fd[1], "\n", 1);
		}
		else
		{
			write(exp_fd[1], cmd->cmd_args[i], eq - cmd->cmd_args[i]);
			write(exp_fd[1], "=", 1);
			write(exp_fd[1], eq + 1, ft_strlen(eq + 1));
			write(exp_fd[1], "\n", 1);
		}
		i++;
	}
	write(exp_fd[1], "\0", 1);
}

void	export_helper(t_command *cmd, int *exp_fd, int *change, int i)
{
	char	*eq;

	while (cmd->env)
	{
		write(exp_fd[1], cmd->env->name, ft_strlen(cmd->env->name));
		write(exp_fd[1], "=", 1);
		i = 1;
		while (cmd->cmd_args[i])
		{
			eq = ft_strchr(cmd->cmd_args[i], '=');
			if (eq != NULL && *(eq + 1) != '\0'
				&& ft_strncmp(cmd->env->name, cmd->cmd_args[i],
					eq - cmd->cmd_args[i]) == 0)
			{
				write(exp_fd[1], eq + 1, ft_strlen(eq + 1));
				(*change)++;
			}
			i++;
		}
		if (*change == 0 && cmd->env->value != NULL)
			write(exp_fd[1], cmd->env->value, ft_strlen(cmd->env->value));
		write(exp_fd[1], "\n", 1);
		cmd->env = cmd->env->next;
	}
}

void	export(t_command *cmd, int *exp_fd)
{
	int	i;
	int	change;

	if (cmd->cmd_args[1] == NULL)
	{
		export_print(cmd->env);
		return ;
	}
	change = 0;
	export_helper(cmd, exp_fd, &change, i);
	export_cmd_args(cmd, exp_fd, change);
}
