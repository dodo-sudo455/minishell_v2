/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 15:00:59 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/19 15:03:44 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	t_session	ss;

	(void)argc;
	(void)argv;
	ctx_init(&ctx, envp);
	ss = session_make();
	session_prompt(&ctx, &ss);
	session_parse(&ctx, &ss);
	exec_heredoc(&ctx, &ss.cmdlst);
	session_clear(&ctx, &ss);
	ctx_clear(&ctx);
	return (0);
}
