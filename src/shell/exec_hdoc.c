/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:20:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/27 13:34:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "shell.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#define HDOC_FNAME "/tmp/minishell-heredoc"

static void	_set_sig_parent(t_ctx *c_ref, struct sigaction *oact)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	safe_sigaction(c_ref, SIGINT, &sa, oact);
}

static void	_set_sig_child(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
}

static void	_handle_hdoc_child(
	t_ctx *c_ref, int fd, const char *delim, bool is_expand)
{
	char	*input;

	_set_sig_child(c_ref);
	while (1)
	{
		input = safe_readline(c_ref, "> ");
		if (!input)
		{
			util_puterr("minishell: warning: \
here-document delimited by end-of-file (wanted `");
			util_puterr(delim);
			util_puterr("')\n");
			exit(0);
		}
		if (ft_strcmp(input, delim) == 0)
			break ;
		if (is_expand)
			ctx_expand(c_ref, &input);
		safe_write(c_ref, fd, input);
		safe_write(c_ref, fd, "\n");
		safe_free(c_ref, input);
	}
	safe_free(c_ref, input);
	safe_close(c_ref, fd);
	exit(0);
}

static int	_handle_hdoc(t_ctx *c_ref, t_redir *red_ref)
{
	struct sigaction	oact;
	int					fd;
	pid_t				pid;
	int					status;

	_set_sig_parent(c_ref, &oact);
	fd = safe_open(c_ref, HDOC_FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	red_ref->docfd = safe_open(c_ref, HDOC_FNAME, O_RDONLY, 0);
	unlink(HDOC_FNAME);
	if (safe_fork(c_ref, &pid) == 0)
	{
		_handle_hdoc_child(c_ref, fd, red_ref->s, !red_ref->has_quote);
	}
	safe_close(c_ref, fd);
	waitpid(pid, &status, 0);
	safe_sigaction(c_ref, SIGINT, &oact, NULL);
	return (util_parse_status(status));
}

t_error	exec_hdoc(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	t_lst	*cmd_nod;
	t_lst	*red_nod;
	t_redir	*red_ref;
	int		status;

	cmd_nod = cmdlst_ref->next;
	while (cmd_nod && cmd_nod != cmdlst_ref)
	{
		red_nod = ((t_cmd *)(cmd_nod->data))->redlst.next;
		while (red_nod && red_nod != &((t_cmd *)(cmd_nod->data))->redlst)
		{
			red_ref = red_nod->data;
			if (red_ref->t == REDIR_HDOC)
			{
				status = _handle_hdoc(c_ref, red_ref);
				if (status == 130)
					return (ERROR_ABORT);
			}
			red_nod = red_nod->next;
		}
		cmd_nod = cmd_nod->next;
	}
	return (ERROR_OK);
}
