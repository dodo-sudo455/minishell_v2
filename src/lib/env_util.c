/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:37:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 17:50:56 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*getenv(t_ctx *c_ref, const char *key)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	nod_ref = c_ref->envlst.next;
	while (nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		if (ft_strcmp(env_ref->key, key) == 0)
			return (safe_strdup(c_ref, ""));
		nod_ref = nod_ref->next;
	}
	return (safe_strdup(c_ref, ""));
}

void	expand(t_ctx *c_ref, char **s)
{
	t_vec	vec;
	size_t	i;
	bool	is_in_quote;

	vec = ft_vec_make(ft_strlen(*s));
	is_in_quote = false;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
		{
			is_in_quote = !is_in_quote;
			i += 1;
			continue ;
		}
		safe_vec_push(c_ref, &vec, (*s)[i]);
		i += 1;
	}
	safe_free(c_ref, *s);
	*s = safe_vec_to_str(c_ref, &vec);
	safe_vec_clear(c_ref, &vec);
}
