/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:19:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 17:12:45 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

bool	token_is_redir(const t_token *tok_ref)
{
	return (tok_ref->t == TOKEN_REDIR_IN
		|| tok_ref->t == TOKEN_REDIR_OUT
		|| tok_ref->t == TOKEN_REDIR_HDOC
		|| tok_ref->t == TOKEN_REDIR_APPEND);
}

bool	token_is_meta(const t_token *tok_ref)
{
	return (tok_ref->t != TOKEN_WORD);
}

bool	token_is_word(const t_token *tok_ref)
{
	return (tok_ref->t == TOKEN_WORD);
}

bool	token_is_pipe(const t_token *tok_ref)
{
	return (tok_ref->t == TOKEN_PIPE);
}
