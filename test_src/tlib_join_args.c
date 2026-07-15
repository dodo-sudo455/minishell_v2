/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlib_join_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 19:31:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 20:31:35 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static char	*_append(char *s1, const char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	return (free(s1), res);
}

char	*tlib_join_args(int argc, char **argv)
{
	char	*input;
	int		i;

	input = ft_strdup("");
	if (!input)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		input = _append(input, argv[i]);
		if (!input)
			return (NULL);
		if (i < argc - 1)
		{
			input = _append(input, " ");
			if (!input)
				return (NULL);
		}
		i += 1;
	}
	return (input);
}
