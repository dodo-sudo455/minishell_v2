/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:38:49 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/22 14:28:56 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

// ft_split safe 버전 만들면 라인 수 줄어들 듯..
static char	*_get_cmd_path(t_ctx *c_ref, const char *env_path, t_lst arglst)
{
	char	*cmd;
	char	**paths;
	char	*path;
	char	*candidate;
	size_t	i;

	cmd = arglst.next->data;
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

static char	**_arglst_to_argv(t_ctx *c_ref, t_lst *arglst)
{
	size_t	n;
	char	**argv;
	t_lst	*p;
	size_t	i;

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

static void	cmd_run_path(t_ctx *c_ref, char *cmd_path, t_lst *arglst)
{
	char	**argv;
	char	*errmsg;
	char	*temp;

	if (cmd_path)
	{
		argv = _arglst_to_argv(c_ref, arglst);
		execve(cmd_path, argv, c_ref->envp);
		temp = safe_strjoin(c_ref, "minishell: ", cmd_path);
		errmsg = safe_strjoin(c_ref, temp, ": ");
		perror(errmsg);
		safe_free(c_ref, temp);
		safe_free(c_ref, errmsg);
		safe_split_free(c_ref, argv);
	}
	if (!cmd_path)
	{
		temp = safe_strjoin(c_ref, "minishell: ", arglst->next->data);
		errmsg = safe_strjoin(c_ref, temp, ": command not found\n");
		write(2, errmsg, ft_strlen(errmsg));
		safe_free(c_ref, temp);
		safe_free(c_ref, errmsg);
	}
}

int	cmd_run(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	char	*cmd_path;

	if (cmd_is_built_in(cmd_ref))
	{
		printf("%s\n", cmd_ref->arglst.data);
		return (0);
	}
	if (ft_strchr(cmd_ref->arglst.next->data, '/') == NULL)
		cmd_path = _get_cmd_path(c_ref, getenv("PATH"), cmd_ref->arglst);
	else
		cmd_path = safe_strdup(c_ref, cmd_ref->arglst.next->data);
	cmd_run_path(c_ref, cmd_path, &cmd_ref->arglst);
	safe_free(c_ref, cmd_path);
	return (1);
}
