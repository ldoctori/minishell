/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:33:41 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 15:37:28 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_args_num(char **token_arr)
{
	int	args_num;

	args_num = 0;
	while (token_arr[args_num] && ft_strncmp(token_arr[args_num], "|", 1) != 0)
		args_num++;
	return (args_num);
}

int	is_redir(char **token_arr, int j, t_command *command)
{
	if (ft_strlen(token_arr[j]) == 2 && ft_strncmp(token_arr[j], ">>", 2) == 0)
	{
		command->outfile = token_arr[j + 1];
		command->append_out = 1;
		return (1);
	}
	else if (ft_strlen(token_arr[j]) == 2
		&& ft_strncmp(token_arr[j], "<<", 2) == 0)
	{
		command->delimiter = token_arr[j + 1];
		return (1);
	}
	else if (ft_strncmp(token_arr[j], "<", 1) == 0)
	{
		command->infile = token_arr[j + 1];
		return (1);
	}
	else if (ft_strncmp(token_arr[j], ">", 1) == 0)
	{
		command->outfile = token_arr[j + 1];
		return (1);
	}
	return (0);
}

void	set_command(t_command *command, char **envp, t_env *env, int args_num)
{
	command->infile = NULL;
	command->outfile = NULL;
	command->delimiter = NULL;
	command->del_fd = NULL;
	command->envp = envp;
	command->env = env;
	command->append_out = 0;
	command->cmd_args = malloc(sizeof(char *) * (args_num + 1));
}

t_command	*get_command(char **token_arr,
							int args_num, char **envp, t_env *env)
{
	int			i;
	t_command	*command;
	int			j;

	command = malloc(sizeof(t_command));
	set_command(command, envp, env, args_num);
	i = 0;
	j = 0;
	while (j < args_num)
	{
		while (is_redir(token_arr, j, command) != 0)
		{
			j += 2;
			if (j >= args_num)
				break ;
		}
		if (j >= args_num)
			break ;
		set_cmd_args(command, token_arr, i, j);
		i++;
		j++;
	}
	command->cmd_args[i] = NULL;
	return (command);
}

t_command	*get_command_list(char **token_arr, char **envp, t_env *env)
{
	int			args_num;
	t_command	*command;
	t_command	*start;

	if (*token_arr == NULL)
		return (NULL);
	args_num = get_args_num(token_arr);
	command = get_command(token_arr, args_num, envp, env);
	start = command;
	command->next = NULL;
	token_arr += args_num;
	while (*token_arr)
	{
		if (ft_strncmp(*token_arr, "|", 1) == 0)
			token_arr++;
		args_num = get_args_num(token_arr);
		command->next = get_command(token_arr, args_num, envp, env);
		command = command->next;
		command->next = NULL;
		token_arr += args_num;
	}
	return (start);
}
