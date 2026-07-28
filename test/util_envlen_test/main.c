/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 14:22:27 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 14:36:19 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	test(const char *s, size_t expected)
{
	size_t	actual;

	actual = util_envlen(s);
	if (actual == expected)
		return ;
	printf("test(s: %s): expected=%zu, actual=%zu\n",
		s, expected, actual);
}

int	main(void)
{
	test(NULL, 0);
	test("", 0);
	test("1ABC", 0);
	test("+ABC", 0);
	test("?ABC", 0);
	test("A", 1);
	test("_", 1);
	test("ABC", 3);
	test("_ABC123", 7);
	test("A_B_C", 5);
	test("A1B2C3", 6);
	test("A=1", 1);
	test("ABC+DEF", 3);
	test("ABC DEF", 3);
	test("_NAME-PLUS", 5);
	test("___", 3);
	return (0);
}
