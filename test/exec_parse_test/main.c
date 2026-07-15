/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 19:29:21 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 20:31:35 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	t_lst	toklst;
	t_lst	cmdlst;
	char	*input;

	if (ctx_init(&ctx, envp) != ERROR_OK)
		return (geterr(&ctx));
	input = tlib_join_args(argc, argv);
	if (!input)
		return (ctx_drop(&ctx), 1);
	toklst = ft_lst_make();
	parse(&ctx, input, &toklst);
	free(input);
	if (geterr(&ctx))
		return (geterr(&ctx));
	exec_parse(&ctx, &toklst, &cmdlst);
	toklst_clear(&toklst);
	if (geterr(&ctx))
		return (geterr(&ctx));
	cmdlst_log(&cmdlst, 0);
	cmdlst_clear(&cmdlst);
	ctx_drop(&ctx);
	return (ERROR_OK);
}
