/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:31:24 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/06 14:37:55 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	slen;
	char	*d;
	size_t	i;

	slen = ft_strlen(s);
	if (slen < n)
		n = slen;
	d = malloc(sizeof(char) * (n + 1));
	if (!d)
		return (d);
	i = 0;
	while (i < n)
	{
		d[i] = *s;
		i += 1;
		s += 1;
	}
	d[i] = '\0';
	return (d);
}
