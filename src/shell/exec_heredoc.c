/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:20:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/19 14:15:35 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "shell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#define HEREDOC_FNAME "/tmp/minishell-heredoc"

/*
	TODO:
	- error 출력 수정(줄 번호)
*/
static void	_heredoc_readline(t_ctx *c_ref, const char *delim, bool is_expand)
{
	char	*input;

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
		printf("%s\n", input);
		safe_free(c_ref, input);
	}
}

// unlink로 디렉터리 엔트리 삭제하고 열린 fd로만 접근하면 파일이 디스크에 남지 않아 안전하다고 함.. 알아보기
static void	_heredoc_input(t_ctx *c_ref, int fd, const char *delim, bool is_expand)
{
	safe_dup2(c_ref, fd, STDOUT_FILENO);
	safe_close(c_ref, fd);
	_heredoc_readline(c_ref, delim, is_expand);
	exit(0);
}

static int	_handle_heredoc(t_ctx *c_ref, t_redir *red_ref)
{
	pid_t	pid;
	int		status;

	red_ref->fd = safe_open(c_ref, HEREDOC_FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	unlink(HEREDOC_FNAME);
	pid = safe_fork(c_ref);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
		_heredoc_input(c_ref, red_ref->fd, red_ref->s, red_ref->has_quote);
	return (0);
}

static int _handle_cmd(
	t_ctx *c_ref, t_cmd *cmd_ref)
{
	t_lst	*red_node;
	t_redir	*red_ref;
	int		status;
	
	red_node = cmd_ref->redlst.next;
	while (red_node != &cmd_ref->redlst)
	{
		red_ref = red_node->data;
		if (red_ref->t == REDIR_HDOC)
		{
			status = _handle_heredoc(c_ref, red_ref);
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

	cmd_node = cmdlst_ref->next;
	while (cmd_node != cmdlst_ref)
	{
		cmd_ref = cmd_node->data;
		if (_handle_cmd(c_ref, cmd_ref) != ERROR_OK)
			return (ERROR_ABORT);
		cmd_node = cmd_node->next;
	}
	return (ERROR_OK);
}
