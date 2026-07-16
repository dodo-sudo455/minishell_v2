/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:00 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:39:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	safe_vec_clear(t_ctx *c_ref, t_vec *vec_ref)
{
	if (vec_ref->arr)
		safe_free(c_ref, vec_ref->arr);
	*vec_ref = ft_vec_make(0);
}

void	safe_vec_push(t_ctx *c_ref, t_vec *vec_ref, char c)
{
	char	*tmp;

	if (!vec_ref->arr)
	{
		vec_ref->arr = safe_malloc(c_ref, sizeof(char) * vec_ref->cap);
	}
	else if (vec_ref->len == vec_ref->cap)
	{
		tmp = safe_malloc(c_ref, sizeof(char) * vec_ref->cap * 2);
		vec_ref->cap *= 2;
		ft_memcpy(tmp, vec_ref->arr, vec_ref->len);
		safe_free(c_ref, vec_ref->arr);
		vec_ref->arr = tmp;
	}
	vec_ref->arr[vec_ref->len] = c;
	vec_ref->len += 1;
}

void	safe_vec_push_n(t_ctx *c_ref, t_vec *vec_ref, const char *buf, size_t n)
{
	while (n > 0)
	{
		safe_vec_push(c_ref, vec_ref, *buf);
		buf += 1;
		n -= 1;
	}
}

char	*safe_vec_to_str(t_ctx *c_ref, t_vec *vec_ref)
{
	char	*s;

	s = safe_malloc(c_ref, sizeof(char) * (vec_ref->len + 1));
	ft_strlcpy(s, vec_ref->arr, vec_ref->len + 1);
	return (s);
}
