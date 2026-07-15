/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:39:38 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/06 17:40:41 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	_ft_printf_write_s(const char *v)
{
	if (v == NULL)
		return (write(STDOUT_FILENO, "(null)", 6));
	return (write(STDOUT_FILENO, v, ft_strlen(v)));
}
