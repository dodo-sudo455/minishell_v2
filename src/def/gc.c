/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:35:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:39:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_gc	gc_make(void)
{
	return (ft_lst_make());
}

int	gc_push(t_gc *gc_ref, void *p)
{
	return (ft_lst_push_front(gc_ref, p));
}

void	*gc_malloc(t_gc *gc_ref, size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		return (NULL);
	if (gc_push(gc_ref, p) != 0)
	{
		free(p);
		return (NULL);
	}
	return (p);
}

void	gc_free(t_gc *gc_ref, void *p)
{
	t_lst	*nod_ref;

	nod_ref = gc_ref->next;
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

void	gc_clear(t_gc *gc_ref)
{
	ft_lst_clear(gc_ref);
}
