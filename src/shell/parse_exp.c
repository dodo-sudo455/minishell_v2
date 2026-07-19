/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:10:02 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/19 14:03:59 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/**
 *	DESCRIPTION
 *
 *		 It expands env var where the token type is WORD
 *		and it is not a heredoc delimeter.
 */
void	parse_expand(t_ctx *c_ref, t_lst *toklst_ref)
{
	t_lst	*nod_ref;
	t_token	*tok_ref;

	nod_ref = toklst_ref->next;
	while (nod_ref != toklst_ref)
	{
		tok_ref = (t_token *)nod_ref->data;
		if (token_is_word(tok_ref)
			&& (nod_ref->prev != toklst_ref
				&& ((t_token *)nod_ref->prev->data)->t != TOKEN_REDIR_HDOC))
			ctx_expand(c_ref, &tok_ref->s);
		nod_ref = nod_ref->next;
	}
}
