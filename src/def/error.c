/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:02:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:53:19 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_error	geterr(const t_ctx *c_ref)
{
	return (c_ref->err);
}

t_error	seterr(t_ctx *c_ref, t_error err, const char *errparam)
{
	c_ref->err = err;
	c_ref->errparam = safe_strdup(c_ref, errparam);
	return (err);
}

void	logerr(t_ctx *c_ref)
{
	printf("logerr(%d, %s)\n", c_ref->err, c_ref->errparam);
	c_ref->err = ERROR_OK;
	safe_free(c_ref, c_ref->errparam);
	c_ref->errparam = NULL;
}
