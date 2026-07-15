/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_pc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:51:46 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/06 17:52:48 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	_ft_printf_write_pc(void)
{
	char	v;

	v = '%';
	return (write(STDOUT_FILENO, &v, 1));
}
