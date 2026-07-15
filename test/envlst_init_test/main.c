/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:10:50 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/06 16:14:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	ctx_make();
	if (ctx_init(&ctx, envp) != ERROR_OK)
	{
		printf("ctx_init error\n");
		return (1);
	}
	envlst_log(&ctx.envlst, 0);
	ctx_drop(&ctx);
	return (0);
}
