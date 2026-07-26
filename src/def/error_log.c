/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:04:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/25 15:22:58 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static void	_log_quote(const t_ctx *c_ref)
{
	(void)c_ref;
	util_puterr("minishell: syntax error: unexpected quote usage\n");
}

// minishell: syntax error near unexpected token 
static void	_log_syn_near_token(const t_ctx *c_ref)
{
	util_puterr("minishell: syntax error near unexpected token `");
	util_puterr(c_ref->errarg);
	util_puterr("`\n");
}

// minishell: export: `arg`: not a valid identifier
static void	_log_invalid_env(const t_ctx *c_ref)
{
	util_puterr("minishell: export: `");
	util_puterr(c_ref->errarg);
	util_puterr("`: not a valid identifier\n");
}

/**
 *		DESCRIPTION
 *
 *			Print error and reset error state.
 */
void	logerr(t_ctx *c_ref)
{
	if (c_ref->err == ERROR_QUOTE)
		_log_quote(c_ref);
	if (c_ref->err == ERROR_SYN_NEAR_TOKEN)
		_log_syn_near_token(c_ref);
	else if (c_ref->err == ERROR_INVALID_IDENTIFIER)
		_log_invalid_env(c_ref);
	unseterr(c_ref);
}
