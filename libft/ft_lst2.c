/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:05:39 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/03 15:36:23 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lst_is_empty(const t_lst *lst_ref)
{
	return (!lst_ref->next || lst_ref->next == lst_ref);
}

t_lst	*ft_lst_first(t_lst *lst_ref)
{
	if (!lst_ref->next || lst_ref->next == lst_ref)
		return (NULL);
	return (lst_ref->next);
}

t_lst	*ft_lst_last(t_lst *lst_ref)
{
	if (!lst_ref->prev || lst_ref->prev == lst_ref)
		return (NULL);
	return (lst_ref->prev);
}

bool	ft_lst_is_first(const t_lst *lst_ref, const t_lst *nod_ref)
{
	return (lst_ref->next == nod_ref);
}

bool	ft_lst_is_last(const t_lst *lst_ref, const t_lst *nod_ref)
{
	return (lst_ref->prev == nod_ref);
}
