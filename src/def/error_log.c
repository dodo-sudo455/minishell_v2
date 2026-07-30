/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:04:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/30 14:17:10 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static void	_log_quote(const char *errcmd, const char *errarg)
{
	(void)errcmd;
	(void)errarg;
	util_puterr("minishell: syntax error: unexpected quote usage\n");
}

// minishell: syntax error near unexpected token 
static void	_log_syn_near_token(const char *errcmd, const char *errarg)
{
	(void)errcmd;
	util_puterr("minishell: syntax error near unexpected token `");
	util_puterr(errarg);
	util_puterr("'\n");
}

// minishell: export: `arg': not a valid identifier
static void	_log_invalid_identifier(const char *errcmd, const char *errarg)
{
	(void)errcmd;
	util_puterr("minishell: export: `");
	util_puterr(errarg);
	util_puterr("': not a valid identifier\n");
}

// minishell: warning:
// 	here-document at line 1 delimited by end-of-file (wanted `errarg`)
static void	_log_abort(const char *errcmd, const char *errarg)
{
	(void)errcmd;
	util_puterr("minishell: warning: ");
	util_puterr("here-document delimited by end-of-file (wanted `");
	util_puterr(errarg);
	util_puterr("')");
}

/**
 *		DESCRIPTION
 *
 *			Print error and reset error state.
 */
void	logerr(t_error err, const char *errcmd, const char *errarg)
{
	if (err == ERROR_QUOTE)
		_log_quote(errcmd, errarg);
	else if (err == ERROR_SYN_NEAR_TOKEN)
		_log_syn_near_token(errcmd, errarg);
	else if (err == ERROR_INVALID_IDENTIFIER)
		_log_invalid_identifier(errcmd, errarg);
	else if (err == ERROR_ABORT)
		_log_abort(errcmd, errarg);
	else if (err == ERROR_ENV_GOT_ARG)
		logerr_env_got_arg(errcmd, errarg);
	else if (err == ERROR_OPEN)
		logerr_open(errcmd, errarg);
	else
		return ;
}
