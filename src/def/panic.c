/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:30:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 15:01:00 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static void	_print_err(t_error err, const char *s)
{
	(void)err;
	(void)s;
}

void	panic(t_ctx *c_ref, t_error err, const char *s)
{
	_print_err(err, s);
	ctx_clear(c_ref);
	exit(err);
}
