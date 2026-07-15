/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:56:00 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/19 14:56:47 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef char	t_byte;

typedef enum e_error
{
	error_ok,
	error_debug,
	error_not_found,
}	t_error;

typedef enum e_type
{
	type_empty,
	type_c,
	type_s,
	type_p,
	type_d,
	type_i,
	type_u,
	type_hl,
	type_hu,
	type_pc,
}	t_type;

typedef struct s_spec
{
	t_type	t;
}	t_spec;

t_error	_ft_printf_read_spec(const char *fmt, size_t *i, t_spec *p);
size_t	_ft_printf_hlen(unsigned int v);
ssize_t	_ft_printf_write(const t_spec *p, va_list *args);
ssize_t	_ft_printf_write_c(char v);
ssize_t	_ft_printf_write_s(const char *v);
ssize_t	_ft_printf_write_p(uintptr_t v);
ssize_t	_ft_printf_write_d(int v);
ssize_t	_ft_printf_write_i(int v);
ssize_t	_ft_printf_write_u(unsigned int v);
ssize_t	_ft_printf_write_hl(unsigned int v);
ssize_t	_ft_printf_write_hu(unsigned int v);
ssize_t	_ft_printf_write_pc(void);
int		ft_printf(const char *s, ...);

#endif // FT_PRINTF_H
