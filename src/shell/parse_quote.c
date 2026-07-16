/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:11:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:39:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	_count(const char *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s == c)
			n += 1;
		s += 1;
	}
	return (n);
}

bool	parse_is_quote_ok(const char *input)
{
	return (_count(input, '\'') % 2 == 0 && _count(input, '\"') % 2 == 0);
}

static void	_remove_quote(t_ctx *c_ref, char **s)
{
	t_vec	vec;
	size_t	i;

	vec = ft_vec_make(ft_strlen(*s));
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' || (*s)[i] == '\"')
		{
			i += 1;
			continue ;
		}
		safe_vec_push(c_ref, &vec, (*s)[i]);
		i += 1;
	}
	*s = safe_vec_to_str(c_ref, &vec);
	safe_vec_clear(c_ref, &vec);
}

void	parse_quote(t_ctx *c_ref, t_lst *toklst_ref)
{
	t_lst	*nod_ref;

	nod_ref = toklst_ref->next;
	while (nod_ref != toklst_ref)
	{
		if (((t_token *)nod_ref->data)->t == TOKEN_WORD)
			_remove_quote(c_ref, &((t_token *)nod_ref->data)->s);
		nod_ref = nod_ref->next;
	}
}
