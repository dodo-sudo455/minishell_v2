/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:07:33 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 20:00:09 by minseobk         ###   ########.fr       */
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
	if (ctx_init(&c, envp) != ERROR_OK)
	{
		free(input);
		return (1);
	}
	toklst = ft_lst_make();
	if (parse_tokenize(&c, input, &toklst) == ERROR_OK)
	{
		if (parse_expand(&c, &toklst) == ERROR_OK)
		{
			if (parse_quote(&c, &toklst) == ERROR_OK)
				toklst_log(&toklst, 0);
		}
	}
	free(input);
	toklst_clear(&toklst);
	ctx_drop(&c);
	return (0);
}
