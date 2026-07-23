/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 20:13:28 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/23 21:05:24 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*
	return value:
		- ok: 0
	
	TODO:
		- 공백 출력하는 거 체크
*/
int	cmd_built_echo(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	bool	is_n_opt;
	t_lst	*arglst;

	is_n_opt = false;
	arglst = cmd_ref->arglst.next;
	if (ft_strcmp(arglst->next->data, "-n"))
	{
		is_n_opt = true;
		arglst = arglst->next;
	}
	while (arglst && arglst != &cmd_ref->arglst)
	{
		printf("%s", arglst->data);
		if (arglst->next)
			printf(" ");
		arglst = arglst->next;
	}
	if (!is_n_opt)
		printf("\n");
	return (0);
}

/*
	TODO:
		- 이동 후 PWD 환경변수 세팅하기
*/
int	cmd_built_cd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*errmsg;
	char	*path;
	size_t	lst_size;

	lst_size = ft_lst_size(&cmd_ref->arglst);
	if (lst_size == 1)
		path = ctx_getenv(c_ref, "HOME");
	else if (lst_size > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	else
		path = cmd_ref->arglst.next->data;
	if (chdir(path))
	{
		errmsg = safe_strjoin(c_ref, "minishell: cd: ", path);
		perror(errmsg);
		safe_free(c_ref, errmsg);
		return (1);
	}
	return (0);
}

/*
	NOTE:
		PWD 환경변수에 현재 디렉토리 경로 저장됨
*/
int	cmd_built_pwd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	printf("%s\n", ctx_getenv(c_ref, "PWD"));
	return (0);
}

int	cmd_built_exit(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	exit(0);
}
