/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:20:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 19:20:32 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	toklst_clear(t_ctx *c_ref, t_lst *toklst_ref)
{
	safe_lst_clear_with(c_ref, toklst_ref, token_drop);
}
