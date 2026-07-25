/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:30:00 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/25 14:20:37 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

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
