/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:21:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 11:05:27 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include "def.h"

typedef struct s_cmd		t_cmd;
typedef enum e_tokentype	t_tokentype;
typedef struct s_token		t_token;
typedef enum e_redirtype	t_redirtype;
typedef struct s_redir		t_redir;

/* ---------------------------------- */
/* cmd                                */
/* ---------------------------------- */

struct s_cmd
{
	t_lst	arglst;
	t_lst	redlst;
	pid_t	pid;
};

t_cmd		*cmd_new(t_ctx *c_ref);
void		cmd_drop(t_ctx *c_ref, t_cmd *cmd_ref);
t_error		cmd_run(t_ctx *c_ref, const t_cmd *cmd_ref);
void		cmdlst_clear(t_ctx *c_ref, t_lst *cmdlst_ref);

/* ---------------------------------- */
/* doc                                */
/* ---------------------------------- */

void		doclst_push(t_ctx *c_ref, t_lst *doclst_ref, const char *fname);
void		doclst_clear(t_ctx *c_ref, t_lst *doclst_ref);

/* ---------------------------------- */
/* log                                */
/* ---------------------------------- */

/* log.c */
void		log_depth(size_t depth);
void		log_lst(const t_lst *lst_ref, size_t depth, bool ln);
void		log_lst_with(const t_lst *lst_ref,
				void (*log_data)(void *, size_t), size_t depth, bool ln);

/* log2.c */
void		log_env(const t_env *env_ref, size_t depth);
void		log_token(const t_token *tok_ref, size_t depth);
void		log_redir(const t_redir *red_ref, size_t depth);

/* log3.c */
void		log_cmd(const t_cmd *cmd_ref, size_t indent);

/* ---------------------------------- */
/* redir                              */
/* ---------------------------------- */

enum e_redirtype
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HDOC,
	REDIR_APPEND
};

/**
 *	FIELDS
 *		- `t`: redirection typed
 *		- `s`: file name or heredoc delimiter
 */
struct s_redir
{
	t_redirtype	t;
	char		*s;
	bool		has_quote;
	int			docfd;
};

t_redir		*redir_new(t_ctx *c_ref, t_redirtype type, const t_token *word_ref);
void		redir_drop(t_ctx *c_ref, t_redir *red_ref);
void		redlst_clear(t_ctx *c_ref, t_lst *redlst_ref);

/* ---------------------------------- */
/* token                              */
/* ---------------------------------- */

enum e_tokentype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_HDOC,
	TOKEN_REDIR_APPEND,
};

struct s_token
{
	t_tokentype	t;
	char		*s;
	bool		has_quote;
};

/* token.c */
t_token		*token_new(t_ctx *c_ref, char *s);
void		token_drop(t_ctx *c_ref, t_token *tok_ref);
t_redirtype	token_to_redirtype(const t_token *t);

/* token_is.c */
bool		token_is_redir(const t_token *tok_ref);
bool		token_is_meta(const t_token *tok_ref);
bool		token_is_word(const t_token *tok_ref);
bool		token_is_pipe(const t_token *tok_ref);

/* toklst.c */
void		toklst_clear(t_ctx *c_ref, t_lst *toklst_ref);

#endif // LIB_H
