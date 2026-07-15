/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 19:26:38 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 19:30:31 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "def.h"
# include "lib.h"

/* ---------------------------------- */
/* prompt                             */
/* ---------------------------------- */

char		*prompt(t_ctx *c_ref);

/* ---------------------------------- */
/* parse                              */
/* ---------------------------------- */

t_lst		parse(t_ctx *c_ref, const char *input);
bool		parse_is_quote_ok(const char *input);
t_lst		parse_tokenize(t_ctx *c_ref, const char *input);
// expand token only with WORD
void		parse_expand(t_ctx *c_ref, t_lst *toklst_ref);
// 1. check quote syntax, 2. remove quote
void		parse_quote(t_ctx *c_ref, t_lst *toklst_ref);

/* ---------------------------------- */
/* exec                               */
/* ---------------------------------- */

void		exec(t_ctx *c_ref, const t_lst *toklst_ref, t_lst *cmdlst_ref);
void		exec_parse(t_ctx *c_ref, const t_lst *toklst_ref,
				t_lst *cmdlst_ref);
void		exec_redir(t_ctx *c_ref, t_lst *cmdlst_ref);
void		exec_pipe(t_ctx *c_ref, t_lst *cmdlst_ref);
void		exec_run(t_ctx*c_ref, t_lst *cmdlst_ref);

#endif // SHELL_H
