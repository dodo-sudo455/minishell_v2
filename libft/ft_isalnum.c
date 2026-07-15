/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:32:39 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"
/*
	checks  for  an alphanumeric character; it is equivalent to (isalpha(c)
	|| isdigit(c)).

The standards require that the argument c for these functions is
	either EOF or a value that is representable in the type unsigned char.

If the argument c is of type char, it must be cast to
	unsigned char, as in the following example:

		char c;
		...
		res = toupper((unsigned char) c);

This is necessary because char may be the equivalent of
	signed char, in which case a byte where the top bit
	is set would be sign extended when converting to int,
	yielding a value that is outside the range of unsigned char.
*/

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
