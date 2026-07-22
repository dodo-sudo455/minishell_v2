/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:51:53 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/22 14:47:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_cmd	*cmd_new(t_ctx *c_ref)
{
	t_cmd	*cmd_ref;

	cmd_ref = safe_malloc(c_ref, sizeof(t_cmd));
	cmd_ref->arglst = ft_lst_make();
	cmd_ref->redlst = ft_lst_make();
	cmd_ref->pid = -1;
	return (cmd_ref);
}

void	cmd_drop(t_ctx *c_ref, t_cmd *cmd_ref)
{
	safe_lst_clear(c_ref, &cmd_ref->arglst);
	redlst_clear(c_ref, &cmd_ref->redlst);
	safe_free(c_ref, cmd_ref);
}

static void	_cmd_drop(t_ctx *c_ref, void *data)
{
	cmd_drop(c_ref, (t_cmd *)data);
}

void	cmdlst_clear(t_ctx *c_ref, t_lst *cmdlst_ref)
{
	safe_lst_clear_with(c_ref, cmdlst_ref, _cmd_drop);
}

bool	cmd_is_built_in(const t_cmd *cmd_ref)
{
	char	*name;

	if (!cmd_ref || ft_lst_is_empty(&cmd_ref->arglst))
		return (false);
	name = (char *)cmd_ref->arglst.next->data;
	return (ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "exit") == 0);
}
