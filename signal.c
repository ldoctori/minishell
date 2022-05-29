/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:13:05 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/29 18:13:07 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_hand_halper(void)
{
	if (g_last_exit.flag == -1)
	{
		printf("\n");
		printf("%s", g_last_exit.prompt);
	}
	else if (g_last_exit.flag == 0)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
}

void	sig_int_handler(int sig)
{
	int	i;

	if (sig == SIGINT)
	{
		sig_int_hand_halper();
		if (g_last_exit.flag > 0)
		{
			printf("\n");
			i = 0;
			while (g_last_exit.pid[i])
			{
				kill(g_last_exit.pid[i], SIGKILL);
				g_last_exit.exit_status = 130;
				i++;
			}
		}
	}
}
