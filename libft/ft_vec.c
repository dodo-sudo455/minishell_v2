/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 14:05:19 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 17:26:54 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include "_libft.h"
#include <stdlib.h>

t_vec	ft_vec_make(size_t cap)
{
	t_vec	vec;

	vec.arr = NULL;
	vec.len = 0;
	vec.cap = cap;
	return (vec);
}

void	ft_vec_clear(t_vec *vec_ref)
{
	if (vec_ref->arr)
		free(vec_ref->arr);
	ft_memset(vec_ref, 0, sizeof(t_vec));
}

int	ft_vec_push(t_vec *vec_ref, char c)
{
	char	*tmp;

	if (!vec_ref->arr)
	{
		vec_ref->arr = malloc(sizeof(char) * vec_ref->cap);
		if (!vec_ref->arr)
			return (1);
	}
	else if (vec_ref->len == vec_ref->cap)
	{
		tmp = malloc(sizeof(char) * vec_ref->cap * 2);
		if (!tmp)
			return (1);
		vec_ref->cap *= 2;
		ft_memcpy(tmp, vec_ref->arr, vec_ref->len);
		free(vec_ref->arr);
		vec_ref->arr = tmp;
	}
	vec_ref->arr[vec_ref->len] = c;
	vec_ref->len += 1;
	return (0);
}

int	ft_vec_push_n(t_vec *vec_ref, const char *buf, size_t n)
{
	while (n > 0)
	{
		if (ft_vec_push(vec_ref, *buf) != 0)
			return (1);
		buf += 1;
		n -= 1;
	}
	return (0);
}

char	*ft_vec_to_str(t_vec *vec_ref)
{
	char	*s;

	s = malloc(sizeof(char) * (vec_ref->len + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, vec_ref->arr, vec_ref->len);
	s[vec_ref->len] = '\0';
	return (s);
}
