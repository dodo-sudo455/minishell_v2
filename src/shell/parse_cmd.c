/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 17:00:01 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 17:45:26 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_error	_parse_redir(t_ctx *c_ref, t_cmd *cmd_ref, t_lst *nod_ref)
{
	t_token	*tokref_arr[2];
	t_redir	*red_ref;

	tokref_arr[0] = nod_ref->data;
	nod_ref = nod_ref->next;
	tokref_arr[1] = nod_ref->data;
	if (!token_is_word(tokref_arr[1]))
		return (seterr(c_ref, ERROR_SYN, tokref_arr[1]->s));
	red_ref = redir_new(c_ref,
			token_to_redirtype(tokref_arr[0]), tokref_arr[1]->s);
	safe_lst_push(c_ref, &cmd_ref->redlst, red_ref);
	return (ERROR_OK);
}

static t_error	_parse_word(t_ctx *c_ref, t_cmd *cmd_ref, t_lst *nod_ref)
{
	t_token	*tok_ref;

	tok_ref = nod_ref->data;
	safe_lst_push(c_ref, &cmd_ref->arglst, safe_strdup(c_ref, tok_ref->s));
	return (ERROR_OK);
}

static t_error	_parse_pipe(
	t_ctx *c_ref, t_lst *cmdlst_ref, t_cmd **cmd_ref)
{
	if (ft_lst_is_empty(&(*cmd_ref)->arglst))
		return (seterr(c_ref, ERROR_SYN, "|"));
	safe_lst_push(c_ref, cmdlst_ref, *cmd_ref);
	*cmd_ref = cmd_new(c_ref);
	return (ERROR_OK);
}

static t_error	_parse_node(
	t_ctx *c_ref, t_lst *cmdlst_ref, t_cmd **cmd_ref, t_lst **nod_ref)
{
	t_token	*tok_ref;

	tok_ref = (*nod_ref)->data;
	if (token_is_redir(tok_ref))
	{
		_parse_redir(c_ref, *cmd_ref, *nod_ref);
		*nod_ref = (*nod_ref)->next;
		*nod_ref = (*nod_ref)->next;
	}
	else if (token_is_word(tok_ref))
	{
		_parse_word(c_ref, *cmd_ref, *nod_ref);
		*nod_ref = (*nod_ref)->next;
	}
	else if (token_is_pipe(tok_ref))
	{
		_parse_pipe(c_ref, cmdlst_ref, cmd_ref);
		*nod_ref = (*nod_ref)->next;
	}
	else
		panic(c_ref, FATAL_DEBUG, "unexpected token type");
	return (geterr(c_ref));
}

t_error	parse_command(
	t_ctx *c_ref, const t_lst *toklst_ref, t_lst *cmdlst_ref)
{
	t_cmd	*cmd_ref;
	t_lst	*nod_ref;

	*cmdlst_ref = ft_lst_make();
	cmd_ref = cmd_new(c_ref);
	nod_ref = toklst_ref->next;
	while (nod_ref != toklst_ref)
	{
		if (_parse_node(c_ref, cmdlst_ref, &cmd_ref, &nod_ref) != ERROR_OK)
			return (geterr(c_ref));
	}
	safe_lst_push(c_ref, cmdlst_ref, cmd_ref);
	return (ERROR_OK);
}
