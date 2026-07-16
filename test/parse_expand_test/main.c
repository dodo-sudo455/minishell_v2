/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:07:33 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:50:10 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	c;
	t_lst	toklst;
	char	*input;

	if (argc < 2)
		return (0);
	input = tlib_join_args(argc, argv);
	ctx_init(&c, envp);
	toklst = ft_lst_make();
	parse_tokenize(&c, input, &toklst);
	parse_expand(&c, &toklst);
	log_lst_with(&toklst, (void (*)(void *, size_t))log_token, 0, true);
	printf("\n");
	free(input);
	toklst_clear(&c, &toklst);
	ctx_clear(&c);
	return (0);
}
