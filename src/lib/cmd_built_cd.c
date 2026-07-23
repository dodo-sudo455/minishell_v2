/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 22:46:25 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/23 22:46:52 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static char	*_cd_get_path(t_ctx *c_ref, const t_cmd *cmd_ref, size_t lst_size)
{
	char	*path;

	if (lst_size == 1)
	{
		path = ctx_getenv(c_ref, "HOME");
		if (!path || !*path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return (path);
	}
	if (lst_size > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (NULL);
	}
	return (cmd_ref->arglst.next->data);
}

static int	_cd_update_pwd(t_ctx *c_ref, const char *path)
{
	char	cwd[PATH_MAX];
	char	*errmsg;

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

int	cmd_built_cd(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*errmsg;
	char	*path;
	size_t	lst_size;

	lst_size = ft_lst_size(&cmd_ref->arglst);
	path = _cd_get_path(c_ref, cmd_ref, lst_size);
	if (!path)
		return (1);
	if (chdir(path))
	{
		errmsg = safe_strjoin(c_ref, "minishell: cd: ", path);
		perror(errmsg);
		safe_free(c_ref, errmsg);
		return (1);
	}
	return (_cd_update_pwd(c_ref, path));
}
