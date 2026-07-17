/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 16:40:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:56:03 by minseobk         ###   ########.fr       */
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
	if (c_ref->errparam)
		safe_free(c_ref, c_ref->errparam);
	ft_memset(c_ref, 0, sizeof(t_ctx));
}
