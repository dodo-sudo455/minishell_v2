/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:15:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/18 14:28:15 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	d = (char *)malloc(sizeof(char) * (dlen + 1));
	if (d == NULL)
		return (NULL);
	ft_memcpy(d, s1, slen1);
	ft_memcpy(d + slen1, s2, slen2);
	d[dlen] = '\0';
	return (d);
}
