/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:10:02 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:39:29 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse_expand(t_ctx *c_ref, t_lst *toklst_ref)
{
	t_lst	*nod_ref;
	t_token	*tok_ref;

	nod_ref = toklst_ref->next;
	while (nod_ref != toklst_ref)
	{
		tok_ref = (t_token *)nod_ref->data;
		if (token_is_word(tok_ref))
			ctx_expand(c_ref, &tok_ref->s);
		nod_ref = nod_ref->next;
	}
}
