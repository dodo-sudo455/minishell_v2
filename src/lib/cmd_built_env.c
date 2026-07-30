/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 16:44:10 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/26 13:31:11 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	cmd_built_env(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	if (ft_lst_size(&cmd_ref->arglst) > 1)
		return (ctx_abort(c_ref, ERROR_ENV_GOT_ARG, "env", NULL));
	nod_ref = c_ref->envlst.next;
	while (nod_ref && nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		ft_putstr_fd(env_ref->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env_ref->val, STDOUT_FILENO);
		nod_ref = nod_ref->next;
	}
	return (0);
}
