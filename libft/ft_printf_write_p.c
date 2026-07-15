/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:16:51 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/07 13:22:16 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	hlen(uintptr_t v)
{
	size_t	l;

	l = 1;
	while (v >= 16)
	{
		v /= 16;
		l++;
	}
	return (l);
}

static void	swrite_h(t_byte *buf, uintptr_t v)
{
	size_t	l;

	l = hlen(v);
	while (l--)
	{
		buf[l] = "0123456789abcdef"[v % 16];
		v /= 16;
	}
}

ssize_t	_ft_printf_write_p(uintptr_t v)
{
	size_t	size;
	t_byte	*buf;
	ssize_t	ret;

	if (v == 0)
		return (write(STDOUT_FILENO, "(nil)", 5));
	size = hlen(v) + 2;
	buf = malloc(size);
	if (buf == NULL)
		return (-1);
	ft_memcpy(buf, "0x", 2);
	swrite_h(buf + 2, v);
	ret = write(STDOUT_FILENO, buf, size);
	free(buf);
	return (ret);
}
