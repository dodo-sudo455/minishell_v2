/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:14:17 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 14:34:41 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lib.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	_sigint_handler(int sig)
{
	g_sig = sig;
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

static void	_check_sig(t_ctx *c_ref)
{
	if (g_sig == SIGINT)
	{
		c_ref->status = 130;
		g_sig = 0;
	}
}

static void	_exit(t_ctx *c_ref)
{
	int	status;

	status = c_ref->status;
	ctx_clear(c_ref);
	printf("exit\n");
	exit(status);
}

int	prompt(t_ctx *c_ref, char **input)
{
	char	*s;

	*input = NULL;
	_set_signal(c_ref);
	g_sig = 0;
	while (1)
	{
		s = safe_readline(c_ref, "minishell> ");
		_check_sig(c_ref);
		if (!s)
		{
			_exit(c_ref);
		}
		if (!*s)
		{
			safe_free(c_ref, s);
			continue ;
		}
		break ;
	}
	add_history(s);
	*input = s;
	return (ERROR_OK);
}
