/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:11:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 11:45:14 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	parse_is_quote_ok(const char *input)
{
	char	ch;

	ch = 0;
	while (*input)
	{
		if (!ch && (*input == '\'' || *input == '\"'))
			ch = *input;
		else if (ch && *input == ch)
			ch = 0;
		input += 1;
	}
	return (ch == 0);
}

static void	_remove_quote(t_ctx *c_ref, char **s)
{
	t_vec	vec;
	size_t	i;
	bool	is_squote;
	bool	is_dquote;

	vec = ft_vec_make(ft_strlen(*s));
	i = 0;
	is_squote = false;
	is_dquote = false;
	while ((*s)[i])
	{
		if (!is_dquote && (*s)[i] == '\'')
		{
			is_squote = !is_squote;
			i += 1;
			continue ;
		}
		if (!is_squote && (*s)[i] == '"')
		{
			is_dquote = !is_dquote;
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
