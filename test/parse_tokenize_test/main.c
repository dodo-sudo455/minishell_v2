/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:35:24 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 20:00:09 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv)
{
	t_ctx	c;
	t_lst	toklst;
	char	*input;

	if (argc < 2)
		return (0);
	input = tlib_join_args(argc, argv);
	c = ctx_make();
	toklst = ft_lst_make();
	parse_tokenize(&c, input, &toklst);
	toklst_log(&toklst, 0);
	free(input);
	toklst_clear(&toklst);
	return (0);
}
