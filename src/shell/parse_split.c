/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 11:36:37 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 11:36:59 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char	*_skip_space(const char *s)
{
	while (*s == ' ')
		s += 1;
	return (s);
}

static const char	*_skip_quote(const char *s)
{
	char	q;

	q = *s;
	s += 1;
	while (*s && *s != q)
		s += 1;
	if (*s)
		s += 1;
	return (s);
}

static const char	*_find_word_end(const char *s)
{
	while (*s && *s != ' ')
	{
		if (*s == '\'' || *s == '"')
		{
			s = _skip_quote(s);
			continue ;
		}
		s += 1;
	}
	return (s);
}

// split str with delimeter SPACE
void	_parse_split_word(t_ctx *c_ref, const char *s, t_lst *lst_ref)
{
	const char	*p;

	while (*s)
	{
		s = _skip_space(s);
		if (!*s)
			break ;
		p = s;
		s = _find_word_end(s);
		safe_lst_push(c_ref, lst_ref, safe_strndup(c_ref, p, s - p));
	}
}
