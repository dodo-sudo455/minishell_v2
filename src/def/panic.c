/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:30:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:16:24 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static void	_log_fatal(t_fatal err, const char *s)
{
	(void)err;
	(void)s;
}

void	panic(t_ctx *c_ref, t_fatal err, const char *s)
{
	_log_fatal(err, s);
	ctx_clear(c_ref);
	exit(err);
}
