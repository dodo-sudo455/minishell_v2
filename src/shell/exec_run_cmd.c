/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:28:34 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/27 15:28:22 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void	_get_redir_fd(
	t_ctx *c_ref, t_redir *red_ref, int *fd, int *fd2)
{
	if (red_ref->t == REDIR_HDOC)
	{
		*fd = red_ref->docfd;
		*fd2 = STDIN_FILENO;
	}
	else if (red_ref->t == REDIR_IN)
	{
		*fd = open(red_ref->s, O_RDONLY);
		*fd2 = STDIN_FILENO;
	}
	else if (red_ref->t == REDIR_OUT)
	{
		*fd = open(red_ref->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*fd2 = STDOUT_FILENO;
	}
	else if (red_ref->t == REDIR_APPEND)
	{
		*fd = open(red_ref->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
		*fd2 = STDOUT_FILENO;
	}
	else
	{
		panic(c_ref, FATAL_DEBUG, "unknown redir type");
	}
}

static void	_print_open_err(t_ctx *c_ref, t_redir *red_ref)
{
	char	*msg;

	msg = safe_strjoin(c_ref, "minishell: ", red_ref->s);
	perror(msg);
	safe_free(c_ref, msg);
}

static int	_handle_redir(t_ctx *c_ref, t_cmd *cmd_ref)
{
	int		fd;
	int		fd2;
	t_lst	*nod_ref;
	t_redir	*red_ref;

	nod_ref = cmd_ref->redlst.next;
	while (nod_ref && nod_ref != &cmd_ref->redlst)
	{
		red_ref = nod_ref->data;
		_get_redir_fd(c_ref, red_ref, &fd, &fd2);
		if (fd < 0)
		{
			_print_open_err(c_ref, red_ref);
			return (EXIT_FAILURE);
		}
		safe_dup2(c_ref, fd, fd2);
		close(fd);
		nod_ref = nod_ref->next;
	}
	return (ERROR_OK);
}

static int	_exec_run_cmd(t_ctx *c_ref, t_cmd *cmd_ref, int infd, int outfd)
{
	int	status;

	if (infd != -1)
		safe_dup2(c_ref, infd, STDIN_FILENO);
	if (outfd != -1)
		safe_dup2(c_ref, outfd, STDOUT_FILENO);
	status = _handle_redir(c_ref, cmd_ref);
	if (status != ERROR_OK)
		return (status);
	return (cmd_run(c_ref, cmd_ref));
}

/**
 *	DESCRIPTION
 *
 *		 It doesn't handle signal actions because handling depends
 *		on whether the current process is a child process.
 *
 *		 Built-in funcs should duplicate std fds because they
 *		run on parent process.
 */
int	exec_run_cmd(t_ctx *c_ref, t_cmd *cmd_ref, int infd, int outfd)
{
	int	std[2];
	int	is_built;
	int	ret;

	is_built = cmd_is_built_in(cmd_ref);
	if (is_built)
	{
		std[0] = safe_dup(c_ref, STDIN_FILENO);
		std[1] = safe_dup(c_ref, STDOUT_FILENO);
	}
	ret = _exec_run_cmd(c_ref, cmd_ref, infd, outfd);
	if (is_built)
	{
		safe_dup2(c_ref, std[0], STDIN_FILENO);
		close(std[0]);
		safe_dup2(c_ref, std[1], STDOUT_FILENO);
		close(std[1]);
	}
	return (ret);
}
