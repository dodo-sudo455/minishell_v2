/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:44:19 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:42:48 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

int	ft_lst_insert(t_lst *nod_ref, void *data)
{
	t_lst	*new_ref;

	if (!nod_ref->next)
	{
		nod_ref->next = nod_ref;
		nod_ref->prev = nod_ref;
	}
	new_ref = ft_lst_node_new(data);
	if (!new_ref)
		return (1);
	new_ref->next = nod_ref->next;
	new_ref->prev = nod_ref;
	nod_ref->next->prev = new_ref;
	nod_ref->next = new_ref;
	return (0);
}

void	ft_lst_remove(t_lst *nod_ref)
{
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	free(nod_ref->data);
	free(nod_ref);
}

void	ft_lst_remove_with(t_lst *nod_ref, void (*del)(void *))
{
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	del(nod_ref->data);
	free(nod_ref);
}
