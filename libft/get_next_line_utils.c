/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:22:43 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/24 12:29:47 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static inline void	test_and_set(size_t *p, size_t v)
{
	if (p)
		*p = v;
}

void	_gnl_memcpy_s(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == NULL || src == NULL || n == 0)
		return ;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

int	_gnl_strlen_s(char const *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 *	RETURN
 *
 *		`i+1` if `s[i] == c`
 *		`strlen(s)` if `c` is not found
 */
bool	_gnl_strfind_s(size_t *find, const char *s, char c)
{
	size_t	i;

	test_and_set(find, 0);
	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			test_and_set(find, i + 1);
			return (true);
		}
		i++;
	}
	test_and_set(find, i);
	return (false);
}

t_error	_gnl_substr_s(
			char **dst, char const *src, size_t start, size_t len)
{
	size_t	i;

	*dst = NULL;
	if (src == NULL || len == 0)
		return (error_ok);
	*dst = (char *)malloc(sizeof(char) * (len + 1));
	if (*dst == NULL)
		return (error_internal);
	i = 0;
	src += start;
	while (i < len)
		(*dst)[i++] = *src++;
	(*dst)[i] = '\0';
	return (error_ok);
}
