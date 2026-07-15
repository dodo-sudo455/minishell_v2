/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_h.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:32:21 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/07 12:53:44 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	hlen(unsigned int v)
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

static void	swrite_h(t_byte *buf, unsigned int v, const char set[16])
{
	size_t	l;

	l = hlen(v);
	while (l--)
	{
		buf[l] = set[v % 16];
		v /= 16;
	}
}

static ssize_t	write_h(unsigned int v, const char set[16])
{
	size_t	size;
	t_byte	*buf;
	ssize_t	ret;

	size = hlen(v);
	buf = malloc(size);
	if (buf == NULL)
		return (-1);
	swrite_h(buf, v, set);
	ret = write(STDOUT_FILENO, buf, size);
	free(buf);
	return (ret);
}

ssize_t	_ft_printf_write_hl(unsigned int v)
{
	return (write_h(v, "0123456789abcdef"));
}

ssize_t	_ft_printf_write_hu(unsigned int v)
{
	return (write_h(v, "0123456789ABCDEF"));
}
