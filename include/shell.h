/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:26:38 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 16:40:01 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "def.h"
# include "lib.h"

typedef struct s_session	t_session;

/* ---------------------------------- */
/* session                            */
/* ---------------------------------- */

struct s_session
{
	char	*input;
	t_lst	toklst;
	t_lst	cmdlst;
	t_lst	doclst;
};

t_session	session_make(void);
void		session_clear(t_ctx *c_ref, t_session *s_ref);
void		session_run(t_ctx *c_ref, t_session *s_ref);
t_error		session_prompt(t_ctx *c_ref, t_session *s_ref);
t_error		session_parse(t_ctx *c_ref, t_session *s_ref);
t_error		session_exec(t_ctx *c_ref, t_session *s_ref);

/* ---------------------------------- */
/* prompt                             */
/* ---------------------------------- */

t_error		prompt(t_ctx *c_ref, char **input);

/* ---------------------------------- */
/* parse                              */
/* ---------------------------------- */

t_error		parse(t_ctx *c_ref, const char *input, t_lst *toklst_ref);
bool		parse_is_quote_ok(const char *input);
void		parse_tokenize(t_ctx *c_ref, const char *input, t_lst *toklst_ref);
// expand token only with WORD
void		parse_expand(t_ctx *c_ref, t_lst *toklst_ref);
// 1. check quote syntax, 2. remove quote
void		parse_quote(t_ctx *c_ref, t_lst *toklst_ref);
t_error		parse_command(t_ctx *c_ref,
				const t_lst *toklst_ref, t_lst *cmdlst_ref);

/* ---------------------------------- */
/* exec                               */
/* ---------------------------------- */

t_error		exec(t_ctx *c_ref, const t_lst *toklst_ref, t_lst *cmdlst_ref);
void		exec_heredoc(t_ctx *c_ref, t_lst *cmdlst_ref, t_lst *doclst_ref);
void		exec_run(t_ctx*c_ref, t_lst *cmdlst_ref);

#endif // SHELL_H
