/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:24:58 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 18:31:50 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	run_parse_and_log(
	t_ctx *c, t_lst *toklst, t_lst *cmdlst, char *input)
{
	parse_tokenize(c, input, toklst);
	parse_expand(c, toklst);
	parse_quote(c, toklst);
	if (parse_command(c, toklst, cmdlst) != ERROR_OK)
		logerr(c);
	else
	{
		log_lst_with(cmdlst, (void (*)(void *, size_t))log_cmd, 0, true);
		printf("\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	c;
	t_lst	toklst;
	t_lst	cmdlst;
	char	*input;

	if (argc < 2)
		return (0);
	input = tlib_join_args(argc, argv);
	ctx_init(&c, envp);
	toklst = ft_lst_make();
	cmdlst = ft_lst_make();
	run_parse_and_log(&c, &toklst, &cmdlst, input);
	free(input);
	toklst_clear(&c, &toklst);
	cmdlst_clear(&c, &cmdlst);
	ctx_clear(&c);
	return (0);
}
