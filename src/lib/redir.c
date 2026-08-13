/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:31:05 by minseobk          #+#    #+#             */
/*   Updated: 2026/08/13 19:42:09 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <unistd.h>

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
	if (red_ref->docfd >= 0)
	{
		close(red_ref->docfd);
		red_ref->docfd = -1;
	}
	if (red_ref->s)
		safe_free(c_ref, red_ref->s);
	safe_free(c_ref, red_ref);
}
