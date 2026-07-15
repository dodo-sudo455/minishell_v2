/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:32:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
The memcmp() function compares the first n bytes (each interpreted as unsigned
	char) of the memory areas s1 and s2.

The memcmp() function returns an integer
	less than, equal to, or greater than zero
	if the first n bytes of s1 is found, respectively,
	to be less than, to match, or be greater than
	the first n bytes of s2.

For a nonzero return value, the sign is determined
	by the sign of the difference  between
	the first pair of bytes (interpreted as unsigned char)
	that differ in s1 and s2.

If n is zero, the return value is zero.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	size_t			i;

	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != q[i])
			return (p[i] - q[i]);
		i++;
	}
	return (0);
}
