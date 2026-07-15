/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:15:30 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
	find next position which is not `c` or `\0`
 */
static size_t	find_next_pos(char const *s, char c, size_t start)
{
	while (s[start] && s[start] == c)
		start++;
	return (start);
}

/*
	`s[start]` should not be `c` or `\0`.
*/
static size_t	substrlen(char const *s, char c, size_t start)
{
	size_t	l;

	l = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		l++;
	}
	return (l);
}

static size_t	count_str(char const *s, char c)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = 0;
	while (1)
	{
		pos = find_next_pos(s, c, pos);
		if (!s[pos])
			break ;
		count++;
		pos += substrlen(s, c, pos);
	}
	return (count);
}

static int	extract_str(
	char const *s,
	char c,
	size_t count,
	char **sp)
{
	size_t	i;
	size_t	pos;
	size_t	len;

	i = 0;
	pos = 0;
	while (i < count)
	{
		pos = find_next_pos(s, c, pos);
		len = substrlen(s, c, pos);
		sp[i] = ft_substr(s, pos, len);
		if (sp[i] == NULL)
		{
			while (i > 0)
				free(sp[--i]);
			return (0);
		}
		pos += len;
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**sp;

	if (s == NULL)
		return (NULL);
	count = count_str(s, c);
	sp = (char **)malloc(sizeof(char *) * (count + 1));
	if (sp == NULL)
		return (NULL);
	if (!extract_str(s, c, count, sp))
	{
		free(sp);
		return (NULL);
	}
	sp[count] = NULL;
	return (sp);
}
