/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:38:49 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/26 14:29:42 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <errno.h>

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

static char	*_get_cmd_path(t_ctx *c_ref, const char *env_path, t_lst arglst)
{
	char	*cmd;
	char	**paths;
	char	*path;
	char	*candidate;
	size_t	i;

	cmd = arglst.next->data;
	if (!env_path)
		return (NULL);
	paths = safe_split(c_ref, env_path, ':');
	i = 0;
	while (paths[i])
	{
		path = safe_strjoin(c_ref, paths[i], "/");
		candidate = safe_strjoin(c_ref, path, cmd);
		safe_free(c_ref, path);
		if (access(candidate, X_OK) == 0)
			return (safe_split_free(c_ref, paths), candidate);
		safe_free(c_ref, candidate);
		i += 1;
	}
	return (safe_split_free(c_ref, paths), NULL);
}

static char	**_arglst_to_argv(t_ctx *c_ref, const t_lst *arglst)
{
	size_t		n;
	char		**argv;
	const t_lst	*p;
	size_t		i;

	n = ft_lst_size(arglst);
	argv = safe_malloc(c_ref, sizeof(char *) * (n + 1));
	p = arglst->next;
	i = 0;
	while (p && p != arglst)
	{
		argv[i++] = safe_strdup(c_ref, (char *)p->data);
		p = p->next;
	}
	argv[i] = NULL;
	return (argv);
}

static int	cmd_run_path(t_ctx *c_ref, char *cmd_path, const t_lst *arglst)
{
	char	**argv;
	int		status;

	status = 0;
	if (cmd_path)
	{
		argv = _arglst_to_argv(c_ref, arglst);
		execve(cmd_path, argv, c_ref->envp);
		util_puterr("minishell: ");
		perror(cmd_path);
		safe_split_free(c_ref, argv);
		if (errno == ENOENT)
			status = 127;
		else
			status = 126;
	}
	else
	{
		util_puterr("minishell: ");
		util_puterr(arglst->next->data);
		util_puterr(": command not found\n");
		status = 127;
	}
	return (status);
}

int	cmd_run(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*cmd_path;
	int		ret;

	if (ft_lst_is_empty(&cmd_ref->arglst))
		return (0);
	if (cmd_is_built_in(cmd_ref))
		return (_run_built_in(c_ref, cmd_ref));
	if (ft_strchr(cmd_ref->arglst.next->data, '/') == NULL)
		cmd_path = _get_cmd_path(c_ref, getenv("PATH"), cmd_ref->arglst);
	else
		cmd_path = safe_strdup(c_ref, cmd_ref->arglst.next->data);
	ret = cmd_run_path(c_ref, cmd_path, &cmd_ref->arglst);
	safe_free(c_ref, cmd_path);
	return (ret);
}
