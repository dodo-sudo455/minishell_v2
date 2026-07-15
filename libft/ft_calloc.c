/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:32:34 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

/*
allocates memory
	for an array of nmemb elements
	of size bytes each

returns a pointer to the allocated memory.

The memory is set to zero.

If nmemb or size is 0,
	then calloc() returns either NULL,
	or a unique pointer value that can later be
	ksuccessfully passed to free().
	
If the multiplication of nmemb and size would
	result in integer overflow,
	then calloc() returns an error.
	
By contrast, an integer overflow would not be detected
	in the following call to malloc(),
	with the result that an incorrectly
	sized block of memory would be allocated:
	
	malloc(nmemb * size);
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	if (nmemb != 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	i = nmemb * size;
	p = (void *)malloc(i);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, i);
	return (p);
}
