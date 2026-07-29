/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 11:43:28 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/29 11:43:45 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	**arglst_to_arr(t_ctx *c_ref, const t_lst *arglst_ref)
{
	char		**argv;
	const t_lst	*p;
	size_t		i;

	argv = safe_malloc(c_ref,
			sizeof(char *) * (ft_lst_size(arglst_ref) + 1));
	p = arglst_ref->next;
	i = 0;
	while (p && p != arglst_ref)
	{
		argv[i] = safe_strdup(c_ref, (char *)p->data);
		p = p->next;
		i += 1;
	}
	argv[i] = NULL;
	return (argv);
}
