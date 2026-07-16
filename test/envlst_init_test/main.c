/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:10:50 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:39:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;

	(void)argc;
	(void)argv;
	ctx_init(&ctx, envp);
	log_lst_with(&ctx.envlst, (void (*)(void *, size_t))log_env, 0, true);
	printf("\n");
	ctx_clear(&ctx);
	return (0);
}
