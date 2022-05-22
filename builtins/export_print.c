/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:40:09 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/15 16:51:23 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_number(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

void	skip(t_env **s_arr, t_env *middle, int *left, int *right)
{
	while (ft_strcmp(s_arr[*left]->name, middle->name) < 0)
		(*left)++;
	while (ft_strcmp(s_arr[*right]->name, middle->name) > 0)
		(*right)--;
}

void	env_sort(t_env **s_arr, int first, int last)
{
	int		left;
	int		right;
	t_env	*middle;
	t_env	*tmp;

	if (first < last)
	{
		left = first;
		right = last;
		middle = s_arr[(left + right) / 2];
		while (left <= right)
		{
			skip(s_arr, middle, &left, &right);
			if (left <= right)
			{
				tmp = s_arr[left];
				s_arr[left] = s_arr[right];
				s_arr[right] = tmp;
				left++;
				right--;
			}
		}
		env_sort(s_arr, first, right);
		env_sort(s_arr, left, last);
	}
}

void	export_print(t_env *env)
{
	t_env	**env_prt_arr;
	int		i;
	int		size;

	size = env_number(env);
	env_prt_arr = malloc(sizeof(t_env *) * (size + 1));
	i = 0;
	while (env)
	{
		env_prt_arr[i] = env;
		env = env->next;
		i++;
	}
	env_prt_arr[i] = NULL;
	i = 0;
	env_sort(env_prt_arr, 0, size - 1);
	while (env_prt_arr[i])
	{
		printf("declare -x %s=%s\n",
			env_prt_arr[i]->name, env_prt_arr[i]->value);
		i++;
	}
	free(env_prt_arr);
}
