/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_uni2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 13:23:26 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/27 13:30:47 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

int	safe_dup(t_ctx *c_ref, int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd < 0)
		panic(c_ref, FATAL_INTERNAL, "dup failed");
	return (new_fd);
}

void	safe_write(t_ctx *c_ref, int fd, const char *s)
{
	if (write(fd, s, ft_strlen(s)) < 0)
		panic(c_ref, FATAL_INTERNAL, "write failed");
}
