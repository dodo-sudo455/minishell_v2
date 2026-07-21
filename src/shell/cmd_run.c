/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 17:38:49 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/21 17:44:56 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static _free_double(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

/*
	ft_split safe 버전 만들면 라인 수 줄어들 듯..
*/
static char	*_get_cmd_path(t_ctx *c_ref, const char *env_path, t_lst arglst)
{
	char	*cmd;
	char	**paths;
	char	*path;
	char	*candidate;
	size_t	i;

	cmd = arglst.next->data;
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = safe_strjoin(c_ref, paths[i], "/");
		candidate = safe_strjoin(c_ref, path, cmd);
		safe_free(c_ref, path);
		if (access(candidate, X_OK) == 0)
		{
			_free_double(paths);
			return (candidate);
		}
		free(candidate);
		i += 1;
	}
	_free_double(paths);
	return (NULL);
}

// error : 1 return
// ❗ cmd_ref->arglst, c_ref->envlst를 이중 포인터로 저장해야 함
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
	if (cmd_path)
	{
		execve(cmd_path, cmd_ref->arglst, c_ref->envlst);
		perror(safe_strjoin(c_ref, "minishell: ", cmd_path));
	}
	if (!cmd_path)
		write(2, "minishell: command not found\n", 30);
	safe_free(c_ref, cmd_path);
	return (1);
}
