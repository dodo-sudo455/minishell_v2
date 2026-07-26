/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:53:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/26 13:31:11 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*
	DESCIPTION
		- 현재 사용자가 위치한 디렉토리 절대경로 출력
		- PWD 환경변수 값 가져옴
		- PWD 환경변수가 빈값이면 getcwd() 함수 이용
*/
int	cmd_built_pwd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)cmd_ref;
	pwd = ctx_getenv(c_ref, "PWD");
	if (*pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		safe_free(c_ref, pwd);
		return (0);
	}
	safe_free(c_ref, pwd);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ctx_setenv(c_ref, "PWD", cwd);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
