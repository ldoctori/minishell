/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_main_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:11:52 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 18:11:54 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arguments_check(int argc, char **argv)
{
	if (argc > 1 || argv[1] != NULL)
	{
		errno = 1;
		perror("to many arguments");
		exit(1);
	}
}

int	line_check(char *line, char *prompt,
		char **token_arr, t_command *cmd_list_start)
{
	int	cont;

	cont = 0;
	if (!line)
	{
		write(0, "exit\n", 5);
		exit_cmd(line, token_arr, prompt, cmd_list_start);
	}
	if (*line == '\0' || *line == ' ')
	{
		free(prompt);
		free(line);
		cont = 1;
	}
	return (cont);
}

void	prompt_check(char *line, char *prompt,
			char **token_arr, t_command *cmd_list_start)
{
	if (prompt == NULL)
	{
		free_parser(line, token_arr, cmd_list_start);
		exit(EXIT_SUCCESS);
	}
}
