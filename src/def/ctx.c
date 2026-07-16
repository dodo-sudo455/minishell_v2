/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 16:40:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 14:38:43 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_ctx	ctx_make(void)
{
	t_ctx	c;

	ft_memset(&c, 0, sizeof(t_ctx));
	return (c);
}

void	ctx_init(t_ctx *c_ref, char **envp)
{
	*c_ref = ctx_make();
	envlst_init(c_ref, &c_ref->envlst, envp);
}

void	ctx_clear(t_ctx *c_ref)
{
	envlst_clear(c_ref, &c_ref->envlst);
	ctx_session_clear(c_ref);
}

void	ctx_session_clear(t_ctx *c_ref)
{
	ft_lst_clear(&c_ref->memlst);
}
