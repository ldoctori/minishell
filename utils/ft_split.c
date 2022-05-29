/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:36:20 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 09:58:41 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_alloc_elem_helper2(t_struct *ss, unsigned int elem,
			unsigned int *len, char some_c)
{
	if (some_c == '"' || some_c == 39)
	{
		ss->split[elem][*len] = *(ss->s);
		ss->s++;
		(*len)++;
	}
	while (*(ss->s) && *(ss->s) != some_c)
	{
		ss->split[elem][*len] = *(ss->s);
		ss->s++;
		(*len)++;
	}
	if (some_c == '"' || some_c == 39)
	{
		ss->split[elem][*len] = *(ss->s);
		ss->s++;
		(*len)++;
	}
}

void	ft_alloc_elem_helper1(t_struct *ss, unsigned int elem,
			unsigned int len, char quot)
{
	ss->split[elem] = malloc(sizeof(char) * (len + 2));
	if (!(ss->split[elem]))
	{
		ss->split = free_all(ss);
		return ;
	}
	len = 0;
	if (*(ss->s) && *(ss->s) == quot)
		ft_alloc_elem_helper2(ss, elem, &len, quot);
	else if (*(ss->s))
		ft_alloc_elem_helper2(ss, elem, &len, ss->c);
	ss->split[elem][len] = '\0';
}

void	ft_alloc_elem(t_struct *ss, unsigned int elem)
{
	char			*ptr;
	unsigned int	len;
	unsigned int	quot;

	len = 0;
	ptr = ss->s;
	quot = 0;
	if (*ptr == '"' || *ptr == 39)
	{
		quot = *ptr;
		ptr++;
		len++;
		len_ptr_increas(&ptr, &len, quot);
		len++;
	}
	else
		len_ptr_increas(&ptr, &len, ss->c);
	ft_alloc_elem_helper1(ss, elem, len, quot);
}

int	ft_rec(t_struct *ss, unsigned int elem)
{
	char	quot;

	while (*(ss->s) == ss->c && *(ss->s))
		ss->s++;
	if (!(*(ss->s)))
	{
		ss->split[elem] = 0;
		return (0);
	}
	ft_alloc_elem(ss, elem);
	if (*(ss->s) == '"' || *(ss->s) == 39)
	{
		ss->s++;
		quot = *(ss->s);
		while (*(ss->s) != quot)
			ss->s++;
		ss->s++;
	}
	return (ft_rec(ss, elem + 1));
}

char	**ft_split(char *s, char c)
{
	t_struct	ss;

	if (!s)
		return (0);
	ss.s = s;
	ss.c = c;
	ft_split_allocate(&ss);
	if (!ss.split)
		return (0);
	ft_rec(&ss, 0);
	return (ss.split);
}
