/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_abort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 11:56:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 13:37:46 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static int	_err_to_status(t_error err)
{
	if (err == ERROR_OK)
		return (0);
	if (err == ERROR_QUOTE)
		return (2);
	if (err == ERROR_SYN_NEAR_TOKEN)
		return (2);
	if (err == ERROR_ABORT)
		return (130);
	if (err == ERROR_INVALID_IDENTIFIER)
		return (1);
	if (err == ERROR_ENV_GOT_ARG)
		return (1);
	if (err == ERROR_OPEN)
		return (1);
	return (1);
}

int	ctx_abort(
	t_ctx *c_ref, t_error err, const char *errcmd, const char *errarg)
{
	logerr(err, errcmd, errarg);
	c_ref->status = _err_to_status(err);
	return (c_ref->status);
}
