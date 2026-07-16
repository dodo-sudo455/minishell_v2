/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:33:51 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 16:58:02 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	ctx_doclst_push(t_ctx *c_ref, const char *fname)
{
	safe_lst_push(c_ref, &c_ref->doclst, safe_strdup(c_ref, fname));
}

void	ctx_doclst_clear(t_ctx *c_ref)
{
	t_lst	*nod_ref;

	nod_ref = c_ref->doclst.next;
	while (nod_ref != c_ref->doclst.next)
	{
		unlink(nod_ref->data);
		nod_ref = nod_ref->next;
	}
	safe_lst_clear(c_ref, &c_ref->doclst);
}
