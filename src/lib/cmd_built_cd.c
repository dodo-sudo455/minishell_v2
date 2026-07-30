/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 22:46:25 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/30 14:10:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <limits.h>
#include <unistd.h>

static char	*_cd_get_path(t_ctx *c_ref, const t_cmd *cmd_ref, size_t lst_size)
{
	char	*path;

	if (lst_size == 1)
	{
		path = ctx_getenv(c_ref, "HOME");
		if (!path || !*path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			if (path)
				safe_free(c_ref, path);
			return (NULL);
		}
		return (path);
	}
	if (lst_size > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (NULL);
	}
	return (safe_strdup(c_ref, cmd_ref->arglst.next->next->data));
}

static int	_cd_update_pwd(t_ctx *c_ref, const char *path)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*errmsg;

	old_pwd = ctx_getenv(c_ref, "PWD");
	if (*old_pwd)
		ctx_setenv(c_ref, "OLDPWD", old_pwd);
	safe_free(c_ref, old_pwd);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		errmsg = safe_strjoin(c_ref, "minishell: cd: getcwd: ", path);
		perror(errmsg);
		safe_free(c_ref, errmsg);
		return (1);
	}
	ctx_setenv(c_ref, "PWD", cwd);
	return (0);
}

/**
 *	DESCRIPTION
 *		- Move to the path passed as an argument
 *
 *	NOTE
 *		- Save the absolute path of the previous directory in OLDPWD
 *		- Save the absolute path of the new directory in PWD after moving
 */
int	cmd_built_cd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*errmsg;
	char	*path;
	size_t	lst_size;
	int		status;

	lst_size = ft_lst_size(&cmd_ref->arglst);
	path = _cd_get_path(c_ref, cmd_ref, lst_size);
	if (!path)
		return (1);
	if (chdir(path))
	{
		errmsg = safe_strjoin(c_ref, "minishell: cd: ", path);
		perror(errmsg);
		safe_free(c_ref, errmsg);
		safe_free(c_ref, path);
		return (1);
	}
	status = _cd_update_pwd(c_ref, path);
	safe_free(c_ref, path);
	return (status);
}
