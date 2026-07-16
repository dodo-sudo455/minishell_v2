/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:49:33 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 14:58:55 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	safe_lst_clear(t_ctx *c_ref, t_lst *lst_ref)
{
	t_lst	*nod_ref;
	t_lst	*tmp;

	nod_ref = lst_ref->next;
	while (nod_ref && nod_ref != lst_ref)
	{
		tmp = nod_ref->next;
		safe_free(c_ref, nod_ref->data);
		safe_free(c_ref, nod_ref);
		nod_ref = tmp;
	}
	*lst_ref = ft_lst_make();
}

void	safe_lst_clear_with(t_ctx *c_ref, t_lst *lst_ref,
				void (*safe_drop)(t_ctx *, void *))
{
	t_lst	*nod_ref;
	t_lst	*tmp;

	nod_ref = lst_ref->next;
	while (nod_ref && nod_ref != lst_ref)
	{
		tmp = nod_ref->next;
		safe_drop(c_ref, nod_ref->data);
		safe_free(c_ref, nod_ref);
		nod_ref = tmp;
	}
	*lst_ref = ft_lst_make();
}

void	safe_lst_remove(t_ctx *c_ref, t_lst *nod_ref)
{
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	safe_free(c_ref, nod_ref->data);
	safe_free(c_ref, nod_ref);
}

void	safe_lst_remove_with(t_ctx *c_ref,
				t_lst *nod_ref, void (*safe_drop)(t_ctx *, void *))
{
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	safe_drop(c_ref, nod_ref->data);
	safe_free(c_ref, nod_ref);
}
