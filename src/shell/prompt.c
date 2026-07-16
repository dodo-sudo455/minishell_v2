/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:14:17 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 15:08:05 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lib.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	_set_signal(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = _sigint_handler;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	safe_sigaction(c_ref, SIGQUIT, &sa, NULL);
}

char	*prompt(t_ctx *c_ref)
{
	char				*input;

	_set_signal(c_ref);
	while (1)
	{
		input = safe_readline(c_ref, "minishell> ");
		if (!input)
		{
			printf("exit\n");
			ctx_clear(c_ref);
			exit(1);
		}
		if (!*input)
		{
			safe_free(NULL, input);
			continue ;
		}
		break ;
	}
	add_history(input);
	return (input);
}
