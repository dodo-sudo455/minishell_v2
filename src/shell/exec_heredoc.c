/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:20:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/19 12:49:22 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include "shell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>

/*
	TODO:
	- error 출력 수정(줄 번호)
*/
static void	_heredoc_readline(t_ctx *c_ref, char *delim)
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
		printf("%s\n", input);
		safe_free(c_ref, input);
	}
}

// unlink로 디렉터리 엔트리 삭제하고 열린 fd로만 접근하면 파일이 디스크에 남지 않아 안전하다고 함.. 알아보기
static void	_heredoc_input(t_ctx *c_ref, char *fname, char *delim)
{
	int		fd;

	fd = safe_open(c_ref, fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	safe_dup2(c_ref, fd, STDOUT_FILENO);
	safe_close(c_ref, fd);
	_heredoc_readline(c_ref, delim);
	safe_free(c_ref, delim);
	exit(0);
}

static t_error	_heredoc_fork(t_ctx *c_ref, t_redir *red_ref,
								t_lst *doclst_ref, int hd_num)
{
	char	*fname;
	char	*delim;
	pid_t	pid;
	int		status;

	delim = red_ref->s;
	fname = safe_strjoin(c_ref, "/tmp/minishell-heredoc-",
		ft_itoa(hd_num));
	red_ref->s = fname;
	safe_lst_push(c_ref, doclst_ref, fname);
	pid = safe_fork(c_ref);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
		_heredoc_input(c_ref, fname, delim);
}

static t_error _heredoc_process(t_ctx *c_ref, t_cmd *cmd_ref,
										t_lst *doclst_ref, int *hd_num)
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
			status = _heredoc_fork(c_ref, red_ref, doclst_ref, hd_num);
			if (status == 130)
				return (ERROR_ABORT);
			*hd_num += 1;
		}
		red_node = red_node->next;
	}
	return (ERROR_OK);
}

t_error	exec_heredoc(t_ctx *c_ref, t_lst *cmdlst_ref, t_lst *doclst_ref)
{
	t_lst	*cmd_node;
	t_cmd	*cmd_ref;
	int		hd_num;

	hd_num = 0;
	cmd_node = cmdlst_ref->next;
	while (cmd_node != cmdlst_ref)
	{
		cmd_ref = cmd_node->data;
		if (_heredoc_process(c_ref, cmd_ref, doclst_ref, &hd_num) != ERROR_OK)
			return (ERROR_ABORT);
		cmd_node = cmd_node->next;
	}
	return (ERROR_OK);
}
