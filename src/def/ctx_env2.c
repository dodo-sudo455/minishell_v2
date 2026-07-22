/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:12:57 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 15:34:03 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static inline bool	_is_expand_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_' || c == '?');
}

static size_t	_expand(t_ctx *c_ref, t_vec *vec_ref, const char *s, size_t i)
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
	namelen = 0;
	while (ft_isalnum((unsigned char)s[i + namelen]) || s[i + namelen] == '_')
		namelen += 1;
	name = safe_strndup(c_ref, s + i, namelen);
	val = ctx_getenv(c_ref, name);
	safe_vec_push_n(c_ref, vec_ref, val, ft_strlen(val));
	safe_free(c_ref, name);
	safe_free(c_ref, val);
	return (i + namelen);
}

void	ctx_expand(t_ctx *c_ref, char **s)
{
	t_vec	vec;
	size_t	i;
	bool	is_quote;

	vec = ft_vec_make(ft_strlen(*s));
	i = 0;
	is_quote = false;
	while ((*s)[i])
	{
		if (is_quote && (*s)[i] == '\'')
		{
			is_quote = !is_quote;
		}
		else if (!is_quote && (*s)[i] == '$' && _is_expand_start((*s)[i + 1]))
		{
			i = _expand(c_ref, &vec, *s, i);
			continue ;
		}
		safe_vec_push(c_ref, &vec, (*s)[i]);
		i += 1;
	}
	safe_free(c_ref, *s);
	*s = safe_vec_to_str(c_ref, &vec);
	safe_vec_clear(c_ref, &vec);
}
