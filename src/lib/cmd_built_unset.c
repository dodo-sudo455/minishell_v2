/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:11:13 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/25 18:16:37 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	cmd_built_unset(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	int			status;
	t_lst		*nod_ref;
	const char	*arg;

	if (ft_lst_size(&cmd_ref->arglst) <= 1)
		return (0);
	status = 0;
	nod_ref = cmd_ref->arglst.next->next;
	while (nod_ref && nod_ref != &cmd_ref->arglst)
	{
		arg = nod_ref->data;
		if (*arg && util_envlen(arg) == ft_strlen(arg))
			ctx_unsetenv(c_ref, arg);
		nod_ref = nod_ref->next;
	}
	return (status);
}
