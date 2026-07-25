/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:53:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/25 12:53:34 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

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
