/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:01:09 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 16:20:04 by cadda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arguments_check(int argc, char **argv)
{
	if (argc > 1 || argv[1] != NULL)
	{
		errno = 1;
		perror("to many arguments");
		exit(1);
	}
}

t_env	*env_update(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->env != NULL)
			return (cmd->env);
		cmd = cmd->next;
	}
	return (cmd->env);
}

t_env	*go_on(t_command *cmd_list_start, char *line,
			char **token_arr, char *prompt)
{
	t_env	*env;

	env = cmd_list_start->env;
	set_cmd_number(cmd_list_start);
	exit_cmd(line, token_arr, prompt, cmd_list_start);
	if (cmd_list_start->next == 0
		&& ft_strncmp(cmd_list_start->cmd_args[0], "cd", 2) == 0)
		cd(cmd_list_start);
	else
	{
		cmds_executer(cmd_list_start, cmd_list_start->envp);
		env = env_update(cmd_list_start);
	}
	free(prompt);
	free_parser(line, token_arr, cmd_list_start);
	return (env);
}

void	signals_catcher()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	g_last_exit.exit_status = 0;
	g_last_exit.flag = -1;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sig_int_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**token_arr;
	t_command	*cmd_list_start;
	char		*prompt;
	t_env		*env;


	signals_catcher();
	env = get_env_list(envp);
	envp = get_envp_arr(envp);
	while (1)
	{
		prompt = path_for_prompt(envp);
		g_last_exit.prompt = prompt;
		if (prompt == NULL)
		{
			free_parser(line, token_arr, cmd_list_start);
			break ;
		}
		line = readline(prompt);
		if (!line)
		{
			write(0, "exit\n", 5);
			exit_cmd(line, token_arr, prompt, cmd_list_start);
		}
		if (*line == '\0')
		{
			free(prompt);
			free(line);
			continue ;
		}
		add_history(line);
		token_arr = ft_split(line, ' ');
		cmd_list_start = get_command_list(token_arr, envp, env);
		env = go_on(cmd_list_start, line, token_arr, prompt);
		envp = updape_envp_arr(env, envp);
	}
}
