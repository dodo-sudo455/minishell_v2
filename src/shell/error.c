/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:02:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:28:48 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	geterr(const t_session *s_ref)
{
	return (s_ref->err);
}

t_error	seterr(
	t_ctx *c_ref, t_session *s_ref, t_error err, const char *errparam)
{
	(void)c_ref;
	(void)s_ref;
	(void)errparam;
	s_ref->err = err;
	return (err);
}
