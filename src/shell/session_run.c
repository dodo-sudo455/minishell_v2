/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:01:06 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 14:58:48 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Calling \`session_clear\` is not necessary.
void	session_run(t_ctx *c_ref, t_session *s_ref)
{
	if (session_prompt(c_ref, s_ref) != 0)
		return ;
	if (session_parse(c_ref, s_ref) != 0)
		return ;
	if (session_exec(c_ref, s_ref) != 0)
		return ;
}

int	session_prompt(t_ctx *c_ref, t_session *s_ref)
{
	return (prompt(c_ref, &s_ref->input));
}

int	session_parse(t_ctx *c_ref, t_session *s_ref)
{
	if (!parse_is_quote_ok(s_ref->input))
		return (ctx_abort(c_ref, ERROR_QUOTE, NULL, NULL));
	parse_tokenize(c_ref, s_ref->input, &s_ref->toklst);
	if (ft_lst_is_empty(&s_ref->toklst))
		return (1);
	parse_expand(c_ref, &s_ref->toklst);
	parse_split_word(c_ref, &s_ref->toklst);
	parse_quote(c_ref, &s_ref->toklst);
	return (parse_command(c_ref, &s_ref->toklst, &s_ref->cmdlst));
}

int	session_exec(t_ctx *c_ref, t_session *s_ref)
{
	int	status;

	status = exec_hdoc(c_ref, &s_ref->cmdlst);
	if (status != 0)
		return (status);
	exec_run(c_ref, &s_ref->cmdlst);
	return (0);
}
