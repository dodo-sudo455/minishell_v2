/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 19:13:42 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*safe_strdup(t_ctx *c_ref, const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = safe_malloc(c_ref, len + 1);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}

char	*safe_strndup(t_ctx *c_ref, const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (len < n && s[len])
		len += 1;
	dup = safe_malloc(c_ref, len + 1);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i += 1;
	}
	dup[len] = '\0';
	return (dup);
}
