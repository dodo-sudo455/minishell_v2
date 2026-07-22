/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:40:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/22 14:16:38 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

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

char	*safe_strjoin(t_ctx *c_ref, const char *s1, const char *s2)
{
	size_t	slen1;
	size_t	slen2;
	size_t	dlen;
	char	*d;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	dlen = slen1 + slen2;
	d = (char *)safe_malloc(c_ref, sizeof(char) * (dlen + 1));
	if (d == NULL)
		return (NULL);
	ft_memcpy(d, s1, slen1);
	ft_memcpy(d + slen1, s2, slen2);
	d[dlen] = '\0';
	return (d);
}
