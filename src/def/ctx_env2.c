/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:12:57 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 13:42:27 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static inline bool	_is_expand_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_' || c == '?');
}

static size_t	_expand(
	t_ctx *c_ref, t_vec *vec_ref, const char *s, size_t i)
{
	size_t	namelen;
	char	*name;
	char	*val;

	i += 1;
	if (s[i] == '?')
	{
		val = safe_itoa(c_ref, c_ref->status);
		safe_vec_push_n(c_ref, vec_ref, val, ft_strlen(val));
		safe_free(c_ref, val);
		return (i + 1);
	}
	namelen = util_envlen(s + i);
	name = safe_strndup(c_ref, s + i, namelen);
	val = ctx_getenv(c_ref, name);
	safe_vec_push_n(c_ref, vec_ref, val, ft_strlen(val));
	safe_free(c_ref, name);
	safe_free(c_ref, val);
	return (i + namelen);
}

static size_t	_append_single_quoted(
	t_ctx *c_ref, t_vec *vec_ref, const char *s, size_t i)
{
	safe_vec_push(c_ref, vec_ref, s[i]);
	i += 1;
	while (s[i] && s[i] != '\'')
	{
		safe_vec_push(c_ref, vec_ref, s[i]);
		i += 1;
	}
	if (s[i] == '\'')
	{
		safe_vec_push(c_ref, vec_ref, s[i]);
		i += 1;
	}
	return (i);
}

static size_t	_append_double_quoted(
	t_ctx *c_ref, t_vec *vec_ref, const char *s, size_t i)
{
	safe_vec_push(c_ref, vec_ref, s[i]);
	i += 1;
	while (s[i] && s[i] != '"')
	{
		if (s[i] == '$' && _is_expand_start(s[i + 1]))
		{
			i = _expand(c_ref, vec_ref, s, i);
			continue ;
		}
		safe_vec_push(c_ref, vec_ref, s[i]);
		i += 1;
	}
	if (s[i] == '"')
	{
		safe_vec_push(c_ref, vec_ref, s[i]);
		i += 1;
	}
	return (i);
}

void	ctx_expand(t_ctx *c_ref, char **s)
{
	t_vec	vec;
	size_t	i;

	vec = ft_vec_make(ft_strlen(*s));
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			i = _append_single_quoted(c_ref, &vec, *s, i);
		else if ((*s)[i] == '"')
			i = _append_double_quoted(c_ref, &vec, *s, i);
		else if ((*s)[i] == '$' && _is_expand_start((*s)[i + 1]))
			i = _expand(c_ref, &vec, *s, i);
		else
		{
			safe_vec_push(c_ref, &vec, (*s)[i]);
			i += 1;
		}
	}
	safe_free(c_ref, *s);
	*s = safe_vec_to_str(c_ref, &vec);
	safe_vec_clear(c_ref, &vec);
}
