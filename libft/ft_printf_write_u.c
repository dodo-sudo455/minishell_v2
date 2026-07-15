/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:49:05 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/07 12:53:22 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	len(unsigned int v)
{
	size_t	l;

	l = 1;
	while (v >= 10)
	{
		v /= 10;
		l++;
	}
	return (l);
}

static void	swrite(t_byte *buf, unsigned int v)
{
	size_t	l;

	l = len(v);
	while (l--)
	{
		buf[l] = v % 10 + '0';
		v /= 10;
	}
}

ssize_t	_ft_printf_write_u(unsigned int v)
{
	size_t	size;
	t_byte	*buf;
	ssize_t	ret;

	size = len(v);
	buf = malloc(size);
	if (buf == NULL)
		return (-1);
	swrite(buf, v);
	ret = write(STDOUT_FILENO, buf, size);
	free(buf);
	return (ret);
}
