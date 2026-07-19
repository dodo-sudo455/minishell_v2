/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:31:05 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/19 16:16:05 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_redir	*redir_new(t_ctx *c_ref, t_redirtype type, const t_token *word_ref)
{
	t_redir	*red;

	red = safe_malloc(c_ref, sizeof(t_redir));
	red->t = type;
	red->s = safe_strdup(c_ref, word_ref->s);
	red->has_quote = word_ref->has_quote;
	red->docfd = -1;
	return (red);
}

void	redir_drop(t_ctx *c_ref, t_redir *red_ref)
{
	if (red_ref->s)
		safe_free(c_ref, red_ref->s);
	safe_free(c_ref, red_ref);
}
