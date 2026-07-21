/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:20:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/21 17:01:23 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "shell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <signal.h>
#define HEREDOC_FNAME "/tmp/minishell-heredoc"

/*
	TODO:
	- error 출력 수정(줄 번호)
*/
static void	_heredoc_readline(
	t_ctx *c_ref, int fd, const char *delim, bool is_expand)
{
	char				*input;

	while (1)
	{
		input = safe_readline(c_ref, "> ");
		if (!input)
		{
			write(2, "warning\n", 8);
			exit(0);
		}
		if (ft_strcmp(input, delim) == 0)
		{
			safe_free(c_ref, input);
			break ;
		}
		if (is_expand)
			ctx_expand(c_ref, &input);
		if (write(fd, input, ft_strlen(input)) < 0)
			panic(c_ref, FATAL_INTERNAL, "heredoc write failed");
		if (write(fd, "\n", 1) < 0)
			panic(c_ref, FATAL_INTERNAL, "heredoc write failed");
		safe_free(c_ref, input);
	}
}

// unlink로 디렉터리 엔트리 삭제하고 열린 fd로만 접근하면 파일이 디스크에 남지 않아 안전하다고 함.. 알아보기
static void	_heredoc_child(
	t_ctx *c_ref, int fd, const char *delim, bool is_expand)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
	_heredoc_readline(c_ref, fd, delim, is_expand);
	safe_close(c_ref, fd);
	exit(0);
}

static int	_handle_heredoc(
	t_ctx *c_ref, t_redir *red_ref, struct sigaction old_int)
{
	pid_t				pid;
	int					status;

	red_ref->docfd = safe_open(c_ref, HEREDOC_FNAME,
			O_WRONLY | O_CREAT | O_TRUNC, 0600);
	unlink(HEREDOC_FNAME);
	if (safe_fork(c_ref, &pid) > 0)
	{
		waitpid(pid, &status, 0);
		safe_sigaction(c_ref, SIGINT, &old_int, NULL);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		return (status);
	}
	else
		_heredoc_child(c_ref, red_ref->docfd, red_ref->s, !red_ref->has_quote);
	return (0);
}

static int	_handle_cmd(t_ctx *c_ref, t_cmd *cmd_ref)
{
	t_lst				*red_node;
	t_redir				*red_ref;
	int					status;
	struct sigaction	sa;
	struct sigaction	old_int;

	if (!cmd_ref->redlst.next)
		return (ERROR_OK);
	red_node = cmd_ref->redlst.next;
	while (red_node && red_node != &cmd_ref->redlst)
	{
		red_ref = red_node->data;
		if (red_ref->t == REDIR_HDOC)
		{
			sa.sa_flags = 0;
			safe_sigemptyset(c_ref, &sa.sa_mask);
			sa.sa_handler = SIG_IGN;
			safe_sigaction(c_ref, SIGINT, &sa, &old_int);
			status = _handle_heredoc(c_ref, red_ref, old_int);
			if (status == 130)
				return (ERROR_ABORT);
		}
		red_node = red_node->next;
	}
	return (ERROR_OK);
}

t_error	exec_heredoc(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	t_lst	*cmd_node;
	t_cmd	*cmd_ref;

	if (!cmdlst_ref->next)
		return (ERROR_OK);
	cmd_node = cmdlst_ref->next;
	while (cmd_node && cmd_node != cmdlst_ref)
	{
		cmd_ref = cmd_node->data;
		if (_handle_cmd(c_ref, cmd_ref) != ERROR_OK)
			return (ERROR_ABORT);
		cmd_node = cmd_node->next;
	}
	return (ERROR_OK);
}
