/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:28:34 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/22 14:08:07 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void static	_set_signal_child(t_ctx *c_ref)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	safe_sigemptyset(c_ref, &sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	safe_sigaction(c_ref, SIGINT, &sa, NULL);
}

int	_handle_redir_flag(t_redirtype t, const char *s, int *file_fd)
{
	int	flag;

	if (t == REDIR_IN || t == REDIR_HDOC)
	{
		flag = O_RDONLY;
		*file_fd = STDIN_FILENO;
		return (open(s, flag));
	}
	else if (t == REDIR_OUT)
	{
		flag = (O_WRONLY | O_CREAT | O_TRUNC);
		*file_fd = STDOUT_FILENO;
		return (open(s, flag, 0644));
	}
	else if (t == REDIR_APPEND)
	{
		flag = (O_WRONLY | O_CREAT | O_APPEND);
		*file_fd = STDOUT_FILENO;
		return (open(s, flag, 0644));
	}
}

void	_handle_redir(t_ctx *c_ref, t_cmd *cmd_ref)
{
	int		fd;
	int		file_fd;
	t_lst	*red_node;
	t_redir	*red_ref;
	char	*errmsg;

	red_node = cmd_ref->redlst.next;
	while (red_node && red_node != &cmd_ref->redlst)
	{
		red_ref = red_node->data;
		fd = _handle_redir_flag(red_ref->t, red_ref->s, &file_fd);
		if (fd < 0)
		{
			errmsg = safe_strjoin(c_ref, "minishell: ", red_ref->s);
			perror(errmsg);
			safe_free(c_ref, errmsg);
			exit(EXIT_FAILURE);
		}
		safe_dup2(c_ref, fd, file_fd);
		close(fd);
		red_node = red_node->next;
	}
}

/*
	- signal 설정
	- 파일 디스크립터 리디렉션
	- cmd 실행
*/
int	exec_run_cmd(t_ctx *c_ref, t_cmd *cmd_ref, int infd, int outfd)
{
	int	tmp_stdin;
	int	tmp_stdout;
	int	ret;

	ret = 0;
	if (cmd_is_built_in(cmd_ref))
	{
		tmp_stdin = dup(STDIN_FILENO);
		tmp_stdout = dup(STDOUT_FILENO);
	}
	_set_signal_child(c_ref);
	if (infd != -1)
		safe_dup2(c_ref, infd, STDIN_FILENO);
	if (outfd != -1)
		safe_dup2(c_ref, outfd, STDOUT_FILENO);
	_handle_redir(c_ref, cmd_ref);
	ret = cmd_run(c_ref, cmd_ref);
	if (cmd_is_built_in(cmd_ref))
	{
		safe_dup2(c_ref, tmp_stdin, STDIN_FILENO);
		close(tmp_stdin);
		safe_dup2(c_ref, tmp_stdout, STDOUT_FILENO);
		close(tmp_stdout);
	}
	return (ret);
}
