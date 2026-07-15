/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:33:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
	copies up to `size - 1` characters (src -> dst)
	guarantee to NUL-terminate the result if size > 0
	src must be NUL-terminated
	Return the length of src

RETURN VALUES

the initial length of dst plus the length of src

if strlcat() traverses size characters without finding a NUL,
	the length of the string is considered to be size
	and the destination string will not be NUL-terminated
	(since there was no space for the NUL).

This keeps strlcat() from running off the end of a string.

In practice this should not happen
	(as it means that either size is incorrect or that dst is not a
	proper “C” string).

The check exists to prevent potential security problems in incorrect code.
*/
// 0  1  2  3  4  5  6  7  8
// a  b  c  \0

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	i;
	size_t	j;
	size_t	dlen;

	slen = ft_strlen(src);
	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	dlen = i;
	while (i + 1 < size && src[j])
		dst[i++] = src[j++];
	if (i < size)
		dst[i] = '\0';
	return (dlen + slen);
}
