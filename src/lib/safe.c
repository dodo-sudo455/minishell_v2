/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_stdlib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:41:03 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 18:49:17 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*safe_malloc(t_ctx *c_ref, size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p || ft_lst_push_front(&c_ref->memlst, p) != 0)
	{
		free(p);
		panic(c_ref, ERROR_INTERNAL, NULL);
	}
	return (p);
}

void	safe_free(t_ctx *c_ref, void *p)
{
	t_lst	*nod_ref;

	nod_ref = c_ref->memlst.next;
	while (nod_ref)
	{
		if (nod_ref->data == p)
		{
			ft_lst_remove(nod_ref);
			break ;
		}
		nod_ref = nod_ref->next;
	}
}
