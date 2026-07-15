/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:09:19 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 19:18:50 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static inline t_tokentype	_map_type(const char *s)
{
	if (ft_strcmp(s, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(s, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(s, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(s, "<<") == 0)
		return (TOKEN_REDIR_HDOC);
	if (ft_strcmp(s, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	return (TOKEN_WORD);
}

static inline bool	_has_quote(const char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (true);
		s += 1;
	}
	return (false);
}

t_token	*token_new(t_ctx *c_ref, char *s)
{
	t_token	*tok_ref;

	tok_ref = safe_malloc(c_ref, sizeof(t_token));
	tok_ref->t = _map_type(s);
	tok_ref->s = s;
	tok_ref->has_quote = _has_quote(s);
	return (tok_ref);
}

void	token_drop(t_ctx *c_ref, t_token *tok_ref)
{
	if (!tok_ref)
		return ;
	if (tok_ref->s)
		safe_free(c_ref, tok_ref->s);
	safe_free(c_ref, tok_ref);
}

t_redirtype	token_to_redirtype(const t_token *t)
{
	if (t->t == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (t->t == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (t->t == TOKEN_REDIR_HDOC)
		return (REDIR_HDOC);
	if (t->t == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_IN);
}
