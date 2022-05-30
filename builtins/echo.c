/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:38:10 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 16:14:12 by cadda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(t_command *cmd)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	if (!cmd->cmd_args[i])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		i++;
		new_line = false;
	}
	while (cmd->cmd_args[i])
	{
		printf("%s", cmd->cmd_args[i]);
		if (new_line)
			printf(" ");
		i++;
	}
	printf("\n");
}
