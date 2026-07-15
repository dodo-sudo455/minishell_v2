/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 08:48:33 by minseobk          #+#    #+#             */
/*   Updated: 2025/11/24 12:29:47 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif // BUFFER_SIZE

typedef enum e_error
{
	error_ok,
	error_eof,
	error_debug,
	error_internal,
	error_unknown,
}	t_error;

char	*get_next_line(int fd);
void	_gnl_memcpy_s(void *dst, const void *src, size_t n);
int		_gnl_strlen_s(char const *s);
bool	_gnl_strfind_s(size_t *find, const char *s, char c);
t_error	_gnl_strappend(char **dst, char const *src);
t_error	_gnl_substr_s(
			char **dst, char const *src, size_t start, size_t len);

#endif // GET_NEXT_LINE_H
