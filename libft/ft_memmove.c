/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:32:59 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
copy n bytes from memory area src to memory area dest.

The memory areas may overlap:
	copying takes place as though the bytes in src are
	first copied into a temporary array that does not
	overlap src or dest, and the bytes are then copied
	from the temporary array to dest.

The memmove() function returns a pointer to dest.
*/

static void	move(
	unsigned char *d,
	const unsigned char *s,
	size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	move_rev(
	unsigned char *d,
	const unsigned char *s,
	size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0)
		return (dest);
	if (src < dest)
		move_rev(dest, src, n);
	else
		move(dest, src, n);
	return (dest);
}
