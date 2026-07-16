/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 15:35:24 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:50:10 by minseobk         ###   ########.fr       */
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
	log_lst_with(&toklst, (void (*)(void *, size_t))log_token, 0, true);
	printf("\n");
	free(input);
	toklst_clear(&c, &toklst);
	return (0);
}
