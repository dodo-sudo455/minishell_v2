/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:05:28 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 15:07:33 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	_redir_drop(t_ctx *c_ref, void *red_ref)
{
	redir_drop(c_ref, (t_redir *)red_ref);
}

void	redlst_clear(t_ctx *c_ref, t_lst *redlst_ref)
{
	safe_lst_clear_with(c_ref, redlst_ref, _redir_drop);
}
