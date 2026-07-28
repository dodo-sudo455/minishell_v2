/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:52:04 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/27 20:04:39 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

// minishell: errcmd: `errarg': unexpected argument
void	logerr_env_got_arg(const char *errcmd, const char *errarg)
{
	util_puterr("minishell: ");
	util_puterr(errcmd);
	util_puterr(": `");
	util_puterr(errarg);
	util_puterr("': unexpected argument\n");
}

// minishell: errarg: perror
void	logerr_open(const char *errcmd, const char *errarg)
{
	(void)errcmd;
	util_puterr("minishell: ");
	perror(errarg);
}
