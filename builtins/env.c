/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:17:23 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 12:17:52 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_env *env)
{	
	while (env)
	{
		printf("%s", env->name);
		if (env->value)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
}
