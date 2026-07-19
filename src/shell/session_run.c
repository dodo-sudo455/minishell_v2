/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:01:06 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/19 15:03:49 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Calling `session_clear` is not necessary.
void	session_run(t_ctx *c_ref, t_session *s_ref)
{
	if (session_prompt(c_ref, s_ref) != ERROR_OK)
		logerr(c_ref);
	else if (session_parse(c_ref, s_ref) != ERROR_OK)
		logerr(c_ref);
	else if (session_exec(c_ref, s_ref) != ERROR_OK)
		logerr(c_ref);
}

t_error	session_prompt(t_ctx *c_ref, t_session *s_ref)
{
	return (prompt(c_ref, &s_ref->input));
}

t_error	session_parse(t_ctx *c_ref, t_session *s_ref)
{
	if (!parse_is_quote_ok(s_ref->input))
		return (seterr(c_ref, ERROR_QUOTE, NULL));
	parse_tokenize(c_ref, s_ref->input, &s_ref->toklst);
	parse_expand(c_ref, &s_ref->toklst);
	parse_quote(c_ref, &s_ref->toklst);
	if (parse_command(c_ref, &s_ref->toklst, &s_ref->cmdlst) != ERROR_OK)
		return (geterr(c_ref));
	return (ERROR_OK);
}

// TODO
t_error	session_exec(t_ctx *c_ref, t_session *s_ref)
{
	if (exec_heredoc(c_ref, &s_ref->cmdlst) != ERROR_OK)
		return (geterr(c_ref));
	return (ERROR_OK);
}
