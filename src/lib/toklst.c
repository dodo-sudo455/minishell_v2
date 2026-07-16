/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:20:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 15:08:00 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	_token_drop(t_ctx *c_ref, void *data)
{
	token_drop(c_ref, (t_token *)data);
}

void	toklst_clear(t_ctx *c_ref, t_lst *toklst_ref)
{
	safe_lst_clear_with(c_ref, toklst_ref, _token_drop);
}
