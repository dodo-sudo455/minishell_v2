/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_lst2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:07:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 11:46:50 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

void	safe_lst_push(t_ctx *c_ref, t_lst *lst_ref, void *data)
{
	t_lst	*new_nod;

	if (!lst_ref->prev)
	{
		lst_ref->next = lst_ref;
		lst_ref->prev = lst_ref;
	}
	new_nod = safe_malloc(c_ref, sizeof(t_lst));
	new_nod->data = data;
	new_nod->next = lst_ref;
	new_nod->prev = lst_ref->prev;
	lst_ref->prev->next = new_nod;
	lst_ref->prev = new_nod;
}

void	*safe_lst_pop_front(t_ctx *c_ref, t_lst *lst_ref)
{
	t_lst	*nod;
	void	*data;

	if (!lst_ref->next || lst_ref->next == lst_ref)
		return (NULL);
	nod = lst_ref->next;
	data = nod->data;
	nod->prev->next = nod->next;
	nod->next->prev = nod->prev;
	safe_free(c_ref, nod);
	return (data);
}

t_lst	*safe_lst_insert(t_ctx *c_ref, t_lst *nod_ref, void *data)
{
	t_lst	*new_nod;

	if (!nod_ref->next)
	{
		nod_ref->next = nod_ref;
		nod_ref->prev = nod_ref;
	}
	new_nod = safe_malloc(c_ref, sizeof(t_lst));
	new_nod->data = data;
	new_nod->next = nod_ref->next;
	new_nod->prev = nod_ref;
	nod_ref->next->prev = new_nod;
	nod_ref->next = new_nod;
	return (new_nod);
}
