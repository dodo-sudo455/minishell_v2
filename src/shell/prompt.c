/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:14:17 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:11:09 by minseobk         ###   ########.fr       */
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

t_error	prompt(t_ctx *c_ref, char **input)
{
	char	*s;

	*input = NULL;
	_set_signal(c_ref);
	while (1)
	{
		s = safe_readline(c_ref, "minishell> ");
		if (!s)
		{
			panic(c_ref, FATAL_EXIT, NULL);
		}
		if (!*s)
		{
			safe_free(NULL, input);
			continue ;
		}
		break ;
	}
	add_history(s);
	*input = s;
	return (ERROR_OK);
}
