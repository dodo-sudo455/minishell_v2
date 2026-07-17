/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:13:28 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:55:06 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_session	session_make(void)
{
	t_session	s;

	s.input = NULL;
	s.toklst = ft_lst_make();
	s.cmdlst = ft_lst_make();
	s.doclst = ft_lst_make();
	return (s);
}

// TODO: add `doclst_clear`
void	session_clear(t_ctx *c_ref, t_session *s_ref)
{
	safe_free(c_ref, s_ref->input);
	toklst_clear(c_ref, &s_ref->toklst);
	cmdlst_clear(c_ref, &s_ref->cmdlst);
	ft_memset(s_ref, 0, sizeof(t_session));
}
