/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:23:51 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 18:29:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void		log_cmd(const t_cmd *cmd_ref, size_t indent);

void	log_env(const t_env *env_ref, size_t depth)
{
	log_depth(depth);
	printf("{\n");
	log_depth(depth + 1);
	printf("key: \"%s\"\n", env_ref->key);
	log_depth(depth + 1);
	printf("val: \"%s\"\n", env_ref->val);
	log_depth(depth);
	printf("}");
}

static const char	*tokentype_to_str(t_tokentype t)
{
	if (t == TOKEN_WORD)
		return ("TOKEN_WORD");
	else if (t == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (t == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	else if (t == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	else if (t == TOKEN_REDIR_HDOC)
		return ("TOKEN_REDIR_HDOC");
	else if (t == TOKEN_REDIR_APPEND)
		return ("TOKEN_REDIR_APPEND");
	return ("UNKNOWN");
}

static const char	*redirtype_to_str(t_redirtype t)
{
	if (t == REDIR_IN)
		return ("REDIR_IN");
	else if (t == REDIR_OUT)
		return ("REDIR_OUT");
	else if (t == REDIR_HDOC)
		return ("REDIR_HDOC");
	else if (t == REDIR_APPEND)
		return ("REDIR_APPEND");
	return ("UNKNOWN");
}

void	log_token(const t_token *tok_ref, size_t depth)
{
	log_depth(depth);
	printf("{\n");
	log_depth(depth + 1);
	printf("t: %s\n", tokentype_to_str(tok_ref->t));
	log_depth(depth + 1);
	printf("s: \"%s\"\n", tok_ref->s);
	log_depth(depth + 1);
	if (tok_ref->has_quote)
		printf("has_quote: true\n");
	else
		printf("has_quote: false\n");
	log_depth(depth);
	printf("}");
}

void	log_redir(const t_redir *red_ref, size_t depth)
{
	log_depth(depth);
	printf("{\n");
	log_depth(depth + 1);
	printf("t: %s\n", redirtype_to_str(red_ref->t));
	log_depth(depth + 1);
	printf("s: \"%s\"\n", red_ref->s);
	log_depth(depth);
	printf("}");
}
