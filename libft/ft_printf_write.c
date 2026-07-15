/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:03:35 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/06 18:24:05 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	_ft_printf_write(const t_spec *p, va_list *args)
{
	if (p->t == type_c)
		return (_ft_printf_write_c((char)va_arg(*args, int)));
	if (p->t == type_s)
		return (_ft_printf_write_s(va_arg(*args, char *)));
	if (p->t == type_p)
		return (_ft_printf_write_p(va_arg(*args, uintptr_t)));
	if (p->t == type_d)
		return (_ft_printf_write_d(va_arg(*args, int)));
	if (p->t == type_i)
		return (_ft_printf_write_i(va_arg(*args, int)));
	if (p->t == type_u)
		return (_ft_printf_write_u(va_arg(*args, unsigned int)));
	if (p->t == type_hl)
		return (_ft_printf_write_hl(va_arg(*args, unsigned int)));
	if (p->t == type_hu)
		return (_ft_printf_write_hu(va_arg(*args, unsigned int)));
	if (p->t == type_pc)
		return (_ft_printf_write_pc());
	return (-1);
}
