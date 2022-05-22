/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:18:58 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 12:19:16 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_cmd(char *line, char **token_arr, char *prompt, t_command *command)
{
	if (command->next != NULL
		|| ft_strncmp(command->cmd_args[0], "exit", 4) != 0)
		return ;
	free_env_list(command->env);
	free_parser(line, token_arr, command);
	free(prompt);
	exit(EXIT_SUCCESS);
}
