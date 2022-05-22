/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:58:44 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 09:37:24 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_helper(t_command *cmd, int *exp_fd, int cmd_len)
{
	if (ft_strncmp(cmd->cmd_args[0], "env", cmd_len) == 0)
	{
		env(cmd->env);
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "export", cmd_len) == 0)
	{
		export(cmd, exp_fd);
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "unset", cmd_len) == 0)
	{
		unset(cmd, exp_fd);
		return (1);
	}
	return (0);
}

int	is_builtin(t_command *cmd, int *exp_fd)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd->cmd_args[0]);
	if (ft_strncmp(cmd->cmd_args[0], "cd", cmd_len) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd_args[0], "pwd", cmd_len) == 0)
	{
		pwd();
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "echo", cmd_len) == 0)
	{
		echo_cmd(cmd);
		return (1);
	}
	else if (ft_strncmp(cmd->cmd_args[0], "exit", cmd_len) == 0)
		return (1);
	return (is_builtin_helper(cmd, exp_fd, cmd_len));
}
