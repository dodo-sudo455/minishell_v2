/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:02:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/25 14:33:04 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_error	geterr(const t_ctx *c_ref)
{
	return (c_ref->err);
}

t_error	seterr(
	t_ctx *c_ref, t_error err, const char *errcmd, const char *errarg)
{
	unseterr(c_ref);
	c_ref->err = err;
	if (errcmd)
		c_ref->errcmd = safe_strdup(c_ref, errcmd);
	if (errarg)
		c_ref->errarg = safe_strdup(c_ref, errarg);
	return (err);
}

void	unseterr(t_ctx *c_ref)
{
	c_ref->err = ERROR_OK;
	if (c_ref->errcmd)
		safe_free(c_ref, c_ref->errcmd);
	c_ref->errcmd = NULL;
	if (c_ref->errarg)
		safe_free(c_ref, c_ref->errarg);
	c_ref->errarg = NULL;
}
