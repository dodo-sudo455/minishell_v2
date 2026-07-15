/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:11:28 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/28 21:16:51 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_error	strappend(char **dst, char const *src)
{
	size_t	dlen;
	size_t	slen;
	size_t	len;
	char	*s;

	dlen = _gnl_strlen_s(*dst);
	slen = _gnl_strlen_s(src);
	len = dlen + slen;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (error_internal);
	_gnl_memcpy_s(s, *dst, dlen);
	_gnl_memcpy_s(s + dlen, src, slen);
	s[len] = '\0';
	free(*dst);
	*dst = s;
	return (error_ok);
}

static inline t_error	free_and_return(char *p, t_error ret)
{
	free(p);
	return (ret);
}

static t_error	read_until_newline(int fd, char **s)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	r;

	if (_gnl_strfind_s(NULL, *s, '\n'))
		return (error_ok);
	while (1)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (free_and_return(*s, error_unknown));
		if (r == 0)
			return (error_ok);
		buf[r] = '\0';
		if (strappend(s, buf) != error_ok)
			return (free_and_return(*s, error_internal));
		if (_gnl_strfind_s(NULL, buf, '\n'))
			return (error_ok);
	}
	return (error_ok);
}

char	*get_next_line(int fd)
{
	static char	*prev = NULL;
	char		*buf;
	char		*line;
	size_t		find;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = prev;
	prev = NULL;
	if (read_until_newline(fd, &buf) != error_ok)
		return (NULL);
	_gnl_strfind_s(&find, buf, '\n');
	if (_gnl_substr_s(&line, buf, 0, find) != error_ok)
	{
		free(buf);
		return (NULL);
	}
	if (_gnl_substr_s(&prev, buf, find, _gnl_strlen_s(buf) - find) != error_ok)
	{
		free(buf);
		free(line);
		return (NULL);
	}
	free(buf);
	return (line);
}
