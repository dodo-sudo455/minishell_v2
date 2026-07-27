/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:30:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/26 16:44:21 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>
#include <stdlib.h>

/**
 *	DESCRIPTION
 *
 *		Parent process should ignore on signals.
 *		- SIGINT: SIG_IGN
 *		- SIGQUIT: SIG_IGN
 */
static void	_set_sig_parent(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
	safe_sigaction(c_ref, SIGQUIT, &sa, NULL);
}

/**
 *	DESCRIPTION
 *
 *		Child processes should quit on signals.
 *		- SIGINT: SIG_DFL
 *		- SIGQUIT: SIG_DFL
 */
static void	_set_sig_child(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
	safe_sigaction(c_ref, SIGQUIT, &sa, NULL);
}

/**
 *	DESCRIPTION
 *
 *		It runs `waitpid` on each pid.
 *
 *	RETURN
 *
 *		It returns status code by last process.
 */
static int	_wait_all(t_ctx *c_ref, const t_lst *cmdlst_ref)
{
	int		status;
	t_lst	*nod_ref;

	(void)c_ref;
	status = 0;
	nod_ref = cmdlst_ref->next;
	while (nod_ref && nod_ref != cmdlst_ref)
	{
		if (((t_cmd *)(nod_ref->data))->pid >= 0)
			waitpid(((t_cmd *)(nod_ref->data))->pid, &status, 0);
		nod_ref = nod_ref->next;
	}
	return (util_parse_status(status));
}

/**
 *	DESCRIPTION
 *
 *		- It connects cmds with pipe.
 *		- It runs cmds
 *		- It should not leave any unused fds open.
 */
static void	_run_all(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	int		prevfd;
	int		pipefd[2];
	t_lst	*nod_ref;

	nod_ref = cmdlst_ref->next;
	prevfd = -1;
	while (nod_ref && nod_ref != cmdlst_ref)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		if (nod_ref->next != cmdlst_ref)
			safe_pipe(c_ref, pipefd);
		if (safe_fork(c_ref, &((t_cmd *)nod_ref->data)->pid) == 0)
		{
			_set_sig_child(c_ref);
			exit(exec_run_cmd(c_ref, nod_ref->data, prevfd, pipefd[1]));
		}
		safe_close(c_ref, prevfd);
		safe_close(c_ref, pipefd[1]);
		prevfd = pipefd[0];
		nod_ref = nod_ref->next;
	}
	safe_close(c_ref, prevfd);
}

/**
 *	DESCRIPTION
 *
 *		- If there is no cmd: set status 0.
 *		- If there is single built-in: run cmd without fork.
 *		- Else: set signal handlers and run cmds.
 */
void	exec_run(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	if (ft_lst_is_empty(cmdlst_ref))
	{
		ctx_setstatus(c_ref, 0);
	}
	else if (ft_lst_size(cmdlst_ref) == 1
		&& cmd_is_built_in(cmdlst_ref->next->data))
	{
		ctx_setstatus(c_ref,
			exec_run_cmd(c_ref, cmdlst_ref->next->data, -1, -1));
	}
	else
	{
		_set_sig_parent(c_ref);
		_run_all(c_ref, cmdlst_ref);
		ctx_setstatus(c_ref, _wait_all(c_ref, cmdlst_ref));
	}
}
