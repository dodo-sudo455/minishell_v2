/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:54:41 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 17:54:45 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	log_arg(const char *s, size_t depth)
{
	log_depth(depth);
	printf("\"%s\"", s);
}

void	log_cmd(const t_cmd *cmd_ref, size_t depth)
{
	log_depth(depth);
	printf("{\n");
	log_depth(depth + 1);
	printf("arglst: ");
	log_lst_with(&cmd_ref->arglst,
		(void (*)(void *, size_t))log_arg, depth + 1, false);
	printf("\n");
	log_depth(depth + 1);
	printf("redlst: ");
	log_lst_with(&cmd_ref->redlst,
		(void (*)(void *, size_t))log_redir, depth + 1, true);
	printf("\n");
	log_depth(depth);
	printf("}");
}
