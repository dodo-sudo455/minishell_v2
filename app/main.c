/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:27:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 15:11:46 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <readline/readline.h>
#include <readline/history.h>

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
		session_clear(&ctx, &ss);
	}
	rl_clear_history();
	ctx_clear(&ctx);
	return (0);
}
