/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:38:49 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/29 19:44:01 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <errno.h>
#include <sys/stat.h>
#define STATUS_CANNOT_EXECUTE 126	// `permission denied` or `is a directory`
#define STATUS_NOT_FOUND 127		// `command not found`

/**
 *	DESCRIPTION
 *
 *		It runs a built-in command.
 */
static int	_run_built_in(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	if (!cmd_ref || ft_lst_is_empty(&cmd_ref->arglst))
		return (0);
	if (ft_strcmp(cmd_ref->arglst.next->data, "echo") == 0)
		return (cmd_built_echo(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "cd") == 0)
		return (cmd_built_cd(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "pwd") == 0)
		return (cmd_built_pwd(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "export") == 0)
		return (cmd_built_export(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "unset") == 0)
		return (cmd_built_unset(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "env") == 0)
		return (cmd_built_env(c_ref, cmd_ref));
	if (ft_strcmp(cmd_ref->arglst.next->data, "exit") == 0)
		return (cmd_built_exit(c_ref, cmd_ref));
	return (0);
}

/**
 *	DESCRIPTION
 *
 *		 If the path contains '/', return the copy of it.
 *		Otherwise, find program file in `PATH` env var.
 */
static char	*_get_cmd_path(
	t_ctx *c_ref, const char *cmd_ref)
{
	char	**paths;
	char	*path;
	char	*candidate;
	char	*env_path;
	size_t	i;

	if (ft_strchr(cmd_ref, '/'))
		return (safe_strdup(c_ref, cmd_ref));
	env_path = ctx_getenv(c_ref, "PATH");
	if (!env_path)
		return (NULL);
	paths = safe_split(c_ref, env_path, ':');
	i = 0;
	while (paths[i])
	{
		path = safe_strjoin(c_ref, paths[i], "/");
		candidate = safe_strjoin(c_ref, path, cmd_ref);
		safe_free(c_ref, path);
		if (access(candidate, X_OK) == 0)
			return (safe_free(c_ref, env_path),
				safe_strarr_free(c_ref, paths), candidate);
		safe_free(c_ref, candidate);
		i += 1;
	}
	return (safe_free(c_ref, env_path), safe_strarr_free(c_ref, paths), NULL);
}

/**
 *	DESCRIPTION
 *
 *		It runs command with `execve`.
 */
static int	_cmd_run_path(
	t_ctx *c_ref, char *cmd_path, const t_lst *arglst_ref)
{
	char		**argv;
	char		**envp;
	int			err;

	argv = arglst_to_arr(c_ref, arglst_ref);
	envp = envlst_to_arr(c_ref, &c_ref->envlst);
	execve(cmd_path, argv, envp);
	err = errno;
	util_puterr("minishell: ");
	perror(cmd_path);
	safe_strarr_free(c_ref, envp);
	safe_strarr_free(c_ref, argv);
	if (err == ENOENT)
		return (STATUS_NOT_FOUND);
	else
		return (STATUS_CANNOT_EXECUTE);
}

/**
 *	DESCRIPTION
 *
 *		 It determines if the argument is a built-in or normal
 *		command and run the command.
 *
 *		 It handles errors:
 *			- 126: the user doesn't have permission for the program.
 *			- 127: the program is not found.
 */
int	cmd_run(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char		*cmd_path;
	int			ret;
	struct stat	st;

	if (ft_lst_is_empty(&cmd_ref->arglst))
		return (0);
	if (cmd_is_built_in(cmd_ref))
		return (_run_built_in(c_ref, cmd_ref));
	cmd_path = _get_cmd_path(c_ref, cmd_ref->arglst.next->data);
	if (!cmd_path)
	{
		util_puterr("minishell: ");
		util_puterr(cmd_ref->arglst.next->data);
		util_puterr(": command not found\n");
		return (STATUS_NOT_FOUND);
	}
	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		util_puterr("minishell: ");
		util_puterr(cmd_path);
		util_puterr(": Is a directory\n");
		return (STATUS_CANNOT_EXECUTE);
	}
	ret = _cmd_run_path(c_ref, cmd_path, &cmd_ref->arglst);
	return (safe_free(c_ref, cmd_path), ret);
}
