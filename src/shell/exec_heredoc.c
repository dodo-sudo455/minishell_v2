/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:20:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/17 18:35:09 by doyelee          ###   ########.fr       */
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
		input = readline("> ");
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
static void	_heredoc_input(t_ctx *c_ref, t_redir *red_ref,
								t_lst *doclst_ref, int heredoc_num)
{
	char	*fname;
	char	*delim;
	int		fd;

	delim = red_ref->s;
	fname = ft_strjoin("/tmp/minishell-heredoc-", ft_itoa(heredoc_num));
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		panic(c_ref, FATAL_INTERNAL, NULL);
	red_ref->s = fname;
	safe_lst_push(c_ref, doclst_ref, fname);
	if (dup2(fd, STDOUT_FILENO) == -1)
		panic(c_ref, FATAL_INTERNAL, NULL);
	close(fd);
	_heredoc_readline(c_ref, delim);
	safe_free(c_ref, delim);
	exit(0);
}

static void	_heredoc_fork(t_ctx *c_ref, t_redir *red_ref,
								t_lst *doclst_ref, int heredoc_num)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		panic(c_ref, FATAL_INTERNAL, NULL);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	_heredoc_input(c_ref, red_ref, doclst_ref, heredoc_num);
}

void	exec_heredoc(t_ctx *c_ref, t_lst *cmdlst_ref, t_lst *doclst_ref)
{
	t_lst	*cmd_node;
	t_lst	*red_node;
	t_cmd	*cmd_ref;
	t_redir	*red_ref;
	int		heredoc_num;

	heredoc_num = 0;
	cmd_node = cmdlst_ref->next;
	while (cmd_node != cmdlst_ref)
	{
		cmd_ref = cmd_node->data;
		red_node = cmd_ref->redlst.next;
		while (red_node != &cmd_ref->redlst)
		{
			red_ref = red_node->data;
			if (red_ref->t == REDIR_HDOC)
			{
				_heredoc_fork(c_ref, red_ref, doclst_ref, heredoc_num);
				heredoc_num++;
			}
			red_node = red_node->next;
		}
		cmd_node = cmd_node->next;
	}
}
