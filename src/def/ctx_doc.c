/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:33:51 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:10:05 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	doclst_push(t_ctx *c_ref, t_lst *doclst_ref, const char *fname)
{
	safe_lst_push(c_ref, doclst_ref, safe_strdup(c_ref, fname));
}

void	doclst_clear(t_ctx *c_ref, t_lst *doclst_ref)
{
	t_lst	*nod_ref;

	nod_ref = doclst_ref->next;
	while (nod_ref != doclst_ref->next)
	{
		unlink(nod_ref->data);
		nod_ref = nod_ref->next;
	}
	safe_lst_clear(c_ref, &doclst_ref);
}
