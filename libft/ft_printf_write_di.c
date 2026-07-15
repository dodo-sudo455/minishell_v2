/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:08:07 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/06 17:36:17 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	_ft_printf_write_d(int v)
{
	char	*buf;
	size_t	ret;

	buf = ft_itoa(v);
	ret = write(STDOUT_FILENO, buf, ft_strlen(buf));
	free(buf);
	return (ret);
}

ssize_t	_ft_printf_write_i(int v)
{
	return (_ft_printf_write_d(v));
}
