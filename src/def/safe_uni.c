/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_uni.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 14:20:31 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/19 14:28:56 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void	safe_dup2(t_ctx *c_ref, int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		panic(c_ref, FATAL_INTERNAL, NULL);
}

void	safe_close(t_ctx *c_ref, int fd)
{
	if (close(fd) < 0)
		panic(c_ref, FATAL_INTERNAL, NULL);
}

int	safe_open(t_ctx *c_ref, const char *file, int oflag, int opt)
{
	int	fd;

	fd = open(file, oflag, opt);
	if (fd < 0 && errno != ENOENT)
	{
		panic(c_ref, FATAL_INTERNAL, NULL);
	}
	return (fd);
}

pid_t	safe_fork(t_ctx *c_ref)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		panic(c_ref, FATAL_INTERNAL, NULL);
	return (pid);
}
