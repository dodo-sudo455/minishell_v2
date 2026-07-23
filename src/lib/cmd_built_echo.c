/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 20:13:28 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/23 22:47:29 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <limits.h>
#include <unistd.h>

int	cmd_built_echo(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	bool	is_n_opt;
	t_lst	*arglst;

	is_n_opt = false;
	arglst = cmd_ref->arglst.next;
	if (arglst != &cmd_ref->arglst && !ft_strcmp(arglst->data, "-n"))
	{
		is_n_opt = true;
		arglst = arglst->next;
	}
	while (arglst != &cmd_ref->arglst)
	{
		printf("%s", arglst->data);
		if (arglst->next != &cmd_ref->arglst)
			printf(" ");
		arglst = arglst->next;
	}
	if (!is_n_opt)
		printf("\n");
	return (0);
}

int	cmd_built_pwd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	(void)cmd_ref;
	pwd = ctx_getenv(c_ref, "PWD");
	if (pwd && *pwd)
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

int	cmd_built_exit(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	exit(0);
}
