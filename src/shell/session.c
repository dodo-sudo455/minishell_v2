/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:13:28 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 14:55:40 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_session	session_make(void)
{
	t_session	s;

	s.input = NULL;
	s.toklst = ft_lst_make();
	s.cmdlst = ft_lst_make();
	return (s);
}

void	session_clear(t_ctx *c_ref, t_session *s_ref)
{
	safe_free(c_ref, s_ref->input);
	toklst_clear(c_ref, &s_ref->toklst);
	cmdlst_clear(c_ref, &s_ref->cmdlst);
	ft_memset(s_ref, 0, sizeof(t_session));
	unseterr(c_ref);
}
