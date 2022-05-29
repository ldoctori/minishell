/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 09:51:56 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 10:05:41 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_split_allocate_helper(t_struct *ss,
		unsigned int *i, unsigned int *count)
{
	char	quot;

	if (ss->s[*i] == '"' || ss->s[*i] == 39)
	{
		quot = ss->s[*i];
		if (quot == '"')
			(*count)++;
		(*i)++;
		while (ss->s[*i] != quot)
			(*i)++;
		return (1);
	}
	return (0);
}

void	ft_split_allocate(t_struct *ss)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (ss->s[i] != '\0')
	{
		if (ft_split_allocate_helper(ss, &i, &count) == 1)
			i++;
		else if (ss->s[i] == ss->c)
		{
			while (ss->s[i] == ss->c)
				i++;
			if (!(ss->s[i]))
				break ;
			count++;
			continue ;
		}
		if (!(ss->s[i]))
			break ;
		i++;
	}
	ss->split = malloc((count + 2) * sizeof(char *));
	ss->size = count;
}

char	**free_all(t_struct *ss)
{
	unsigned int	elem;

	elem = 0;
	while (ss->split[elem])
	{
		free(ss->split[elem]);
		elem++;
	}
	free(ss->split);
	return (0);
}

void	len_ptr_increas(char **ptr, unsigned int *len, char some_c)
{
	while (**ptr != some_c && **ptr)
	{
		(*ptr)++;
		(*len)++;
	}
}
