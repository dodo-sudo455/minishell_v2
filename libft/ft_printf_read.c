/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:39:08 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/17 15:12:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_type	map_type(char c)
{
	if (c == 'c')
		return (type_c);
	if (c == 's')
		return (type_s);
	if (c == 'p')
		return (type_p);
	if (c == 'd')
		return (type_d);
	if (c == 'i')
		return (type_i);
	if (c == 'u')
		return (type_u);
	if (c == 'x')
		return (type_hl);
	if (c == 'X')
		return (type_hu);
	if (c == '%')
		return (type_pc);
	return (type_empty);
}

t_error	_ft_printf_read_spec(const char *fmt, size_t *i, t_spec *p)
{
	if (fmt[*i] != '%')
		return (error_debug);
	(*i)++;
	p->t = map_type(fmt[(*i)++]);
	if (p->t == type_empty)
		return (error_not_found);
	return (error_ok);
}
