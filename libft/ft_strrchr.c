/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:33:11 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
The strrchr() function returns a pointer to the last occurrence of
	the character c in the string s.

return a pointer to the matched character
	or NULL if the character is not found.

The terminating null byte is considered part of the string,
	so that if c is specified as '\0', these functions return
	a pointer to the terminator.
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	slen;
	size_t	i;
	char	v;

	slen = ft_strlen(s);
	i = slen;
	v = (char)c;
	while (1)
	{
		if (s[i] == v)
			return ((char *)(s + i));
		if (i == 0)
			return (NULL);
		i--;
	}
}
