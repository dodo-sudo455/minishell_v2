/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:30:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/22 14:47:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>
#include <stdlib.h>

static void	_set_sig_parent(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
	safe_sigaction(c_ref, SIGQUIT, &sa, NULL);
}

static int	_to_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

/**
 *	DESCRIPTION
 *
 *		- 
 */
static void	_exec_run(t_ctx *c_ref, t_lst *cmdlst_ref)
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
			exit(exec_run_cmd(c_ref, nod_ref->data, prevfd, pipefd[1]));
		if (prevfd >= 0)
			safe_close(c_ref, prevfd);
		prevfd = pipefd[0];
		if (pipefd[1] >= 0)
			safe_close(c_ref, pipefd[1]);
		nod_ref = nod_ref->next;
	}
	if (prevfd >= 0)
		safe_close(c_ref, prevfd);
}

void	exec_run(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	t_lst	*nod_ref;
	t_cmd	*cmd_ref;
	int		status;

	if (ft_lst_is_empty(cmdlst_ref))
	{
		ctx_setstatus(c_ref, 0);
		return ;
	}
	nod_ref = cmdlst_ref->next;
	if (ft_lst_size(cmdlst_ref) == 1 && cmd_is_built_in(nod_ref->data))
	{
		ctx_setstatus(c_ref,
			exec_run_cmd(c_ref, cmdlst_ref->next->data, -1, -1));
		return ;
	}
	_set_sig_parent(c_ref);
	_exec_run(c_ref, cmdlst_ref);
	while (nod_ref && nod_ref != cmdlst_ref)
	{
		cmd_ref = nod_ref->data;
		if (cmd_ref->pid >= 0)
			waitpid(cmd_ref->pid, &status, 0);
		nod_ref = nod_ref->next;
	}
	ctx_setstatus(c_ref, _to_exit_status(status));
}
