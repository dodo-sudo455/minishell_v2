/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_waitall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 15:00:40 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/26 15:05:18 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>

int	exec_run_waitall(t_ctx *c_ref, const t_lst *cmdlst_ref)
{
	int		status;
	t_lst	*nod_ref;
	t_cmd	*cmd_ref;

	status = 0;
	nod_ref = cmdlst_ref->next;
	while (nod_ref && nod_ref != cmdlst_ref)
	{
		cmd_ref = nod_ref->data;
		if (cmd_ref->pid >= 0)
			waitpid(cmd_ref->pid, &status, 0);
		nod_ref = nod_ref->next;
	}
	return (util_parse_status(status));
}
