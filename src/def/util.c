/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:30:00 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/27 19:37:20 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <fcntl.h>
#include <unistd.h>

size_t	util_envlen(const char *s)
{
	size_t	i;

	if (s[0] == '\0')
		return (0);
	if (ft_isalpha((unsigned char)s[0]) == 0 && s[0] != '_')
		return (0);
	i = 1;
	while (ft_isalnum((unsigned char)s[i]) || s[i] == '_')
		i += 1;
	return (i);
}

ssize_t	util_puterr(const char *s)
{
	return (write(STDERR_FILENO, s, ft_strlen(s)));
}

int	util_parse_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
