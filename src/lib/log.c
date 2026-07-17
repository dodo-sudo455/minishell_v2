/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:00:22 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 18:00:37 by minseobk         ###   ########.fr       */
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

static void	_log_str_data(void *data, size_t depth)
{
	(void)depth;
	printf("%p", data);
}

void	log_lst(const t_lst *lst_ref, size_t depth, bool ln)
{
	log_lst_with(lst_ref, _log_str_data, depth, ln);
}

static inline void	_log_node(
	void (*log_data)(void *, size_t), const t_lst *cur, size_t depth, bool ln)
{
	if (ln)
		printf("\n");
	if (ln)
		log_data(cur->data, depth + 1);
	else
		log_data(cur->data, 0);
	if (ln)
		printf(",");
}

void	log_lst_with(const t_lst *lst_ref,
			void (*log_data)(void *, size_t), size_t depth, bool ln)
{
	const t_lst	*cur;

	printf("[");
	if (!ft_lst_is_empty(lst_ref))
	{
		cur = lst_ref->next;
		while (cur != lst_ref)
		{
			_log_node(log_data, cur, depth, ln);
			cur = cur->next;
			if (!ln && cur != lst_ref)
				printf(", ");
		}
		if (ln)
		{
			printf("\n");
			log_depth(depth);
		}
	}
	printf("]");
}
