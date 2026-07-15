/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:21:28 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 *	RETURN
 * 		index of the next percent symbol
 * 		or '\0'
 */
static inline size_t	next_percent(const char *fmt, size_t i)
{
	while (fmt[i] && fmt[i] != '%')
		i++;
	return (i);
}

static ssize_t	write_and_update(const char *s, size_t n, ssize_t *count)
{
	ssize_t	ret;

	ret = write(STDOUT_FILENO, s, n);
	if (ret >= 0)
		*count += ret;
	return (ret);
}

static ssize_t	write_spec_and_update(
	const char *fmt, size_t *start, va_list *args, ssize_t *count)
{
	t_spec	p;
	ssize_t	ret;

	p.t = type_empty;
	_ft_printf_read_spec(fmt, start, &p);
	ret = _ft_printf_write(&p, args);
	if (ret > 0)
		*count += ret;
	return (ret);
}

/**
 *	RETURN
 *		the number of characters printed
 *		(excluding the null byte used to end output to strings)
 */
int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	size_t	prev;
	size_t	next;
	ssize_t	ret;

	if (fmt == NULL)
		return (-1);
	va_start(args, fmt);
	prev = 0;
	ret = 0;
	while (1)
	{
		next = next_percent(fmt, prev);
		if (write_and_update(fmt + prev, next - prev, &ret) < 0)
			return (-1);
		if (!fmt[next])
			break ;
		if (write_spec_and_update(fmt, &next, &args, &ret) < 0)
			return (-1);
		prev = next;
	}
	va_end(args);
	return (ret);
}
