/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:39:13 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/* return the index of the leftmost valid char */
static size_t	get_left_end(char const *s, char const *set)
{
	size_t	e;

	e = 0;
	while (ft_strchr(set, s[e]))
		e++;
	return (e);
}

/* return the +1 index of the rightmost valid char */
static size_t	get_right_end_plus(char const *s, char const *set, size_t slen)
{
	size_t	e;

	e = slen;
	while (e > 0 && ft_strchr(set, s[e - 1]))
		e--;
	return (e);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	slen;
	size_t	lend;
	size_t	rendp;
	size_t	dsiz;
	char	*d;

	if (s1 == NULL || set == NULL)
		return (NULL);
	slen = ft_strlen(s1);
	lend = get_left_end(s1, set);
	rendp = get_right_end_plus(s1, set, slen);
	if (lend >= rendp)
		dsiz = 1;
	else
		dsiz = rendp - lend + 1;
	d = (char *)malloc(sizeof(char) * dsiz);
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s1 + lend, dsiz);
	return (d);
}
