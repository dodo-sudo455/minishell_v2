/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:53:12 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/30 14:10:43 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/**
 *	DESCRIPTION
 *
 *		- Print the absolute path of the current working directory
 *		- Retrieve the value of the PWD environment variable
 *		- If PWD is empty, use the getcwd() function
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
