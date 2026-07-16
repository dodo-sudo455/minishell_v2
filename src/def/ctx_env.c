/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:37:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 19:43:33 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <stddef.h>

char	*ctx_getenv(t_ctx *c_ref, const char *key)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	nod_ref = c_ref->envlst.next;
	while (nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		if (ft_strcmp(env_ref->key, key) == 0)
			return (safe_strdup(c_ref, env_ref->val));
		nod_ref = nod_ref->next;
	}
	return (safe_strdup(c_ref, ""));
}

static inline bool	_is_name_start(char c)
{
	return (ft_isalpha((unsigned char)c) || c == '_');
}

static inline bool	_is_name_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

static size_t	_expand(t_ctx *c_ref, t_vec *vec_ref, const char *s, size_t i)
{
	size_t	namelen;
	char	*name;
	char	*val;

	namelen = 0;
	i += 1;
	while (_is_name_char(s[i + namelen]))
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
		else if (!is_quote && (*s)[i] == '$' && _is_name_start((*s)[i + 1]))
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
