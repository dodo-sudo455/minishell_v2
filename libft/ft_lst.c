/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:07:25 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 17:26:54 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

t_lst	ft_lst_make(void)
{
	t_lst	lst;

	lst.data = NULL;
	lst.next = NULL;
	lst.prev = NULL;
	return (lst);
}

void	ft_lst_clear(t_lst *lst_ref)
{
	t_lst	*p;
	t_lst	*tmp;

	if (!lst_ref->next)
		return ;
	p = lst_ref->next;
	while (p && p != lst_ref)
	{
		tmp = p->next;
		free(p->data);
		free(p);
		p = tmp;
	}
	*lst_ref = ft_lst_make();
}

void	ft_lst_clear_with(t_lst *lst_ref, void (*del)(void *))
{
	t_lst	*p;
	t_lst	*tmp;

	if (!lst_ref->next)
		return ;
	p = lst_ref->next;
	while (p && p != lst_ref)
	{
		tmp = p->next;
		del(p->data);
		free(p);
		p = tmp;
	}
	*lst_ref = ft_lst_make();
}

size_t	ft_lst_size(const t_lst *lst_ref)
{
	size_t			size;
	const t_lst		*head;

	if (!lst_ref->next)
		return (0);
	size = 0;
	head = lst_ref;
	lst_ref = lst_ref->next;
	while (lst_ref && lst_ref != head)
	{
		lst_ref = lst_ref->next;
		size += 1;
	}
	return (size);
}

t_lst	*ft_lst_node_new(void *data)
{
	t_lst	*nod_ref;

	nod_ref = malloc(sizeof(t_lst));
	if (!nod_ref)
		return (NULL);
	nod_ref->data = data;
	nod_ref->next = NULL;
	nod_ref->prev = NULL;
	return (nod_ref);
}
