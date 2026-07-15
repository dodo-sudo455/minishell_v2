/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:00:22 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 18:15:46 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	log_depth(size_t depth)
{
	size_t	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i += 1;
	}
}

void	log_lst(const t_lst *lst_ref, size_t depth, bool ln)
{
	const t_lst	*cur;

	log_depth(depth);
	printf("[");
	cur = lst_ref->next;
	while (cur != lst_ref)
	{
		if (ln)
			printf("\n");
		log_depth(depth + 1);
		printf("%p", cur->data);
		cur = cur->next;
		if (cur != lst_ref)
			printf(",");
	}
	if (ln)
	{
		printf("\n");
		log_depth(depth);
	}
	printf("]");
}

void	log_lst_with(const t_lst *lst_ref,
			void (*log_data)(void *, size_t), size_t depth, bool ln)
{
	const t_lst	*cur;

	log_depth(depth);
	printf("[");
	cur = lst_ref->next;
	while (cur != lst_ref)
	{
		if (ln)
			printf("\n");
		log_data(cur->data, depth + 1);
		cur = cur->next;
		if (cur != lst_ref)
			printf(",");
	}
	if (ln)
	{
		printf("\n");
		log_depth(depth);
	}
	printf("]");
}
