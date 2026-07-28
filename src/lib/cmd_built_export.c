/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:55:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/27 19:58:37 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	_run_declare_x(t_ctx *c_ref, const t_lst *envlst_ref)
{
	t_lst	**envlst_sorted;
	t_env	*env_ref;
	int		size;
	int		i;

	size = ft_lst_size(envlst_ref);
	if (size == 0)
		return (0);
	envlst_sorted = envlst_sort(c_ref, envlst_ref);
	i = 0;
	while (i < size)
	{
		env_ref = envlst_sorted[i]->data;
		if (env_ref->val)
			ft_printf("declare -x %s=\"%s\"\n", env_ref->key, env_ref->val);
		else
			ft_printf("declare -x %s\n", env_ref->key);
		i += 1;
	}
	return (0);
}

static int	_set(
	t_ctx *c_ref, const char *arg, const char *key, const char *val)
{
	size_t	len;

	len = util_envlen(key);
	if (*key && len == ft_strlen(key))
	{
		ctx_setenv(c_ref, key, val);
		return (0);
	}
	return (seterr(c_ref, ERROR_INVALID_IDENTIFIER, "export", arg));
}

static void	_parse_and_set(t_ctx *c_ref, const char *arg, int *status_ref)
{
	char	*eq;
	char	*key;
	int		status;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = safe_strndup(c_ref, arg, (size_t)(eq - arg));
		status = _set(c_ref, arg, key, eq + 1);
		safe_free(c_ref, key);
	}
	else
	{
		status = _set(c_ref, arg, arg, "");
	}
	if (status == 1)
		*status_ref = 1;
}

int	cmd_built_export(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	t_lst		*nod_ref;
	int			status;
	const char	*arg;

	if (ft_lst_size(&cmd_ref->arglst) == 1)
		return (_run_declare_x(c_ref, &c_ref->envlst));
	nod_ref = cmd_ref->arglst.next->next;
	status = 0;
	while (nod_ref && nod_ref != &cmd_ref->arglst)
	{
		arg = nod_ref->data;
		_parse_and_set(c_ref, arg, &status);
		nod_ref = nod_ref->next;
	}
	return (status);
}
