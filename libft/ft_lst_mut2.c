/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mut2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:51:22 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:42:48 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

int	ft_lst_push_front(t_lst *lst_ref, void *data)
{
	if (!lst_ref->next)
	{
		lst_ref->next = lst_ref;
		lst_ref->prev = lst_ref;
	}
	return (ft_lst_insert(lst_ref, data));
}

int	ft_lst_push(t_lst *lst_ref, void *data)
{
	if (!lst_ref->prev)
	{
		lst_ref->next = lst_ref;
		lst_ref->prev = lst_ref;
	}
	return (ft_lst_insert(lst_ref->prev, data));
}

void	*ft_lst_pop_front(t_lst *lst_ref)
{
	t_lst	*nod_ref;
	void	*data;

	if (!lst_ref->next || lst_ref->next == lst_ref)
		return (NULL);
	nod_ref = lst_ref->next;
	data = nod_ref->data;
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	free(nod_ref);
	return (data);
}

void	*ft_lst_pop(t_lst *lst_ref)
{
	t_lst	*nod_ref;
	void	*data;

	if (!lst_ref->prev || lst_ref->prev == lst_ref)
		return (NULL);
	nod_ref = lst_ref->prev;
	data = nod_ref->data;
	nod_ref->prev->next = nod_ref->next;
	nod_ref->next->prev = nod_ref->prev;
	free(nod_ref);
	return (data);
}
