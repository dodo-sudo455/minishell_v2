/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:18:29 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:10:33 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <signal.h>

void	safe_sigemptyset(t_ctx *c_ref, sigset_t *set)
{
	if (sigemptyset(set) < 0)
		panic(c_ref, FATAL_INTERNAL, "sigemptyset failed");
}

void	safe_sigaction(t_ctx *c_ref, int signum,
				const struct sigaction *act, struct sigaction *oldact)
{
	if (sigaction(signum, act, oldact) < 0)
		panic(c_ref, FATAL_INTERNAL, "sigaction failed");
}
