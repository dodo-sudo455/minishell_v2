/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:27:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:27:11 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	t_session	ss;

	(void)argc;
	(void)argv;
	ctx_init(&ctx, envp);
	ss = session_make();
	while (1)
	{
		session_run(&ctx, &ss);
		printf("Your input is: %s\n", ss.input);
		session_clear(&ctx, &ss);
	}
	ctx_clear(&ctx);
	return (0);
}
