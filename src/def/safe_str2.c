/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:16:30 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/22 14:25:25 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static size_t	_count_str(const char *s, char c)
{
	size_t	count;

	if (s == NULL || s[0] == '\0')
		return (0);
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static size_t	_get_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**safe_split(t_ctx *c_ref, const char *s, char c)
{
	char	**result;
	size_t	count;
	size_t	i;
	size_t	len;

	count = _count_str(s, c);
	result = (char **)safe_malloc(c_ref, sizeof(char *) * (count + 1));
	i = 0;
	while (*s && i < count)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = _get_word_len(s, c);
			result[i++] = safe_strndup(c_ref, s, len);
			s += len;
		}
	}
	result[i] = NULL;
	return (result);
}

void	safe_split_free(t_ctx *c_ref, char **sp)
{
	size_t	i;

	if (sp == NULL)
		return ;
	i = 0;
	while (sp[i])
	{
		safe_free(c_ref, sp[i]);
		i++;
	}
	safe_free(c_ref, sp);
}
