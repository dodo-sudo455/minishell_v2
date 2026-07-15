/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:30:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 18:40:42 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	panic(t_ctx *c_ref, t_error err, const char *s)
{
	log_err(err, s);
	ctx_clear(c_ref);
	exit(err);
}
