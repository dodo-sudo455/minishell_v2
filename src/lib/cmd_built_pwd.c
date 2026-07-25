/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:53:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/25 13:26:03 by doyelee          ###   ########.fr       */
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
		printf("%s\n", pwd);
		return (0);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ctx_setenv(c_ref, "PWD", cwd);
	printf("%s\n", cwd);
	return (0);
}
