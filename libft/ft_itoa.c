/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:14:01 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:37:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

static int	check_neg(int *n)
{
	if (*n >= 0)
		return (0);
	*n = -*n;
	return (1);
}

static size_t	count_digits(int n)
{
	size_t	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	write_digits(char *s, int n, size_t digits)
{
	while (digits > 0)
	{
		s[--digits] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		is_neg;
	size_t	digits;
	char	*s;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	is_neg = check_neg(&n);
	digits = count_digits(n);
	s = malloc(is_neg + digits + 1);
	if (s == NULL)
		return (NULL);
	if (is_neg)
	{
		s[0] = '-';
		write_digits(s + 1, n, digits);
		s[digits + 1] = '\0';
	}
	else
	{
		write_digits(s, n, digits);
		s[digits] = '\0';
	}
	return (s);
}
