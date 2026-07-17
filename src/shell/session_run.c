/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:01:06 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:28:00 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// TODO
static void	_log_err(t_error err, const char *errparam)
{
	printf("log_err(%d, %s)\n", err, errparam);
}

void	session_run(t_ctx *c_ref, t_session *s_ref)
{
	if (session_prompt(c_ref, s_ref) != ERROR_OK)
	{
		_log_err(s_ref->err, s_ref->errparam);
		return ;
	}
	if (session_parse(c_ref, s_ref) != ERROR_OK)
	{
		_log_err(s_ref->err, s_ref->errparam);
		return ;
	}
	if (session_exec(c_ref, s_ref) != ERROR_OK)
	{
		_log_err(s_ref->err, s_ref->errparam);
		return ;
	}
}

t_error	session_prompt(t_ctx *c_ref, t_session *s_ref)
{
	return (prompt(c_ref, &s_ref->input));
}

t_error	session_parse(t_ctx *c_ref, t_session *s_ref)
{
	if (!parse_is_quote_ok(s_ref->input))
		return (seterr(c_ref, s_ref, ERROR_QUOTE, NULL));
	parse_tokenize(c_ref, s_ref->input, &s_ref->toklst);
	parse_expand(c_ref, &s_ref->toklst);
	parse_quote(c_ref, &s_ref->toklst);
	return (ERROR_OK);
}

// TODO
t_error	session_exec(t_ctx *c_ref, t_session *s_ref)
{
	(void)c_ref;
	(void)s_ref;
	return (ERROR_OK);
}
