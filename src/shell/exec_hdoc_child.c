/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:00:00 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 15:08:32 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "shell.h"
#include <signal.h>

#define HDOC_EOF_MSG_0 "minishell: warning: \
here-document delimited by end-of-file (wanted `"

static void	_set_sig_child(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
}

static void	_handle_eof(t_ctx *c_ref, const char *delim)
{
	util_puterr("minishell: warning: \
here-document delimited by end-of-file (wanted `");
	util_puterr(delim);
	util_puterr("')\n");
	ctx_clear(c_ref);
	exit(0);
}

void	exec_hdoc_child(
	t_ctx *c_ref, int fd, const char *delim, bool is_expand)
{
	char	*input;

	_set_sig_child(c_ref);
	while (1)
	{
		input = safe_readline(c_ref, "> ");
		if (!input)
			_handle_eof(c_ref, delim);
		if (ft_strcmp(input, delim) == 0)
		{
			safe_free(c_ref, input);
			break ;
		}
		if (is_expand)
			ctx_expand(c_ref, &input);
		safe_write(c_ref, fd, input);
		safe_write(c_ref, fd, "\n");
		safe_free(c_ref, input);
	}
	safe_close(c_ref, fd);
	ctx_clear(c_ref);
	exit(0);
}
