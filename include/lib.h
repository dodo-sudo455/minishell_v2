/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:21:08 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 19:09:06 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include "def.h"

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
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
};

t_cmd		*cmd_new(t_ctx *c_ref);
void		cmd_drop(t_ctx *c_ref, t_cmd *cmd_ref);
void		cmdlst_clear(t_ctx *c_ref, t_lst *cmdlst_ref);

/* ---------------------------------- */
/* env                                */
/* ---------------------------------- */

struct s_env
{
	char	*key;
	char	*val;
};

t_env		*env_new(t_ctx *c_ref, const char *s);
void		env_drop(t_ctx *c_ref, t_env *env_ref);
void		envlst_init(t_ctx *c_ref, t_lst *envlst_ref, char **envp);
void		envlst_clear(t_ctx *c_ref, t_lst *envlst_ref);
char		*getenv(t_ctx *c_ref, const char *key);
void		expand(t_ctx *c_ref, char **s);


/* ---------------------------------- */
/* log                                */
/* ---------------------------------- */

/* log.c */
void		log_depth(size_t depth);
void		log_lst(const t_lst *lst_ref, size_t depth, bool ln);
void		log_lst_with(const t_lst *lst_ref,
				void (*log_data)(void *, size_t), size_t depth, bool ln);

/* log2.c */
void		log_cmd(const t_cmd *cmd_ref, size_t indent);
void		log_env(const t_env *env_ref, size_t depth);
void		log_token(const t_token *tok_ref, size_t depth);
void		log_redir(const t_redir *red_ref, size_t depth);

/* log_err.c */
void		log_err(t_error err, const char *s);

/* ---------------------------------- */
/* panic                              */
/* ---------------------------------- */

void		panic(t_ctx *c_ref, t_error err, const char *s);

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
};

t_redir		*redir_new(t_ctx *c_ref, t_redirtype type, const char *fname);
void		redir_drop(t_ctx *c_ref, t_redir *red_ref);

/* ---------------------------------- */
/* safe                               */
/* ---------------------------------- */

/* safe.c */
void		*safe_malloc(t_ctx *c_ref, size_t size);
void		safe_free(t_ctx *c_ref, void *p);

/* safe_lst.c */
void		safe_lst_clear(t_ctx *c_ref, t_lst *lst_ref);
void		safe_lst_clear_with(t_ctx *c_ref, t_lst *lst_ref,
				void (*safe_drop)(t_ctx *, void *));
void		safe_lst_remove(t_ctx *c_ref, t_lst *nod_ref);
void		safe_lst_remove_with(t_ctx *c_ref,
				t_lst *nod_ref, void (*safe_drop)(t_ctx *, void *));

/* safe_lst2.c */
void		safe_lst_push(t_ctx *c_ref, t_lst *lst_ref, void *data);
void		*safe_lst_pop_front(t_ctx *c_ref, t_lst *lst_ref);

/* safe_vec.c */
void		safe_vec_clear(t_ctx *c_ref, t_vec *vec_ref);
int			safe_vec_push(t_ctx *c_ref, t_vec *vec_ref, char c);
int			safe_vec_push_n(t_ctx *c_ref,
				t_vec *vec_ref, const char *buf, size_t n);
char		*safe_vec_to_str(t_ctx *c_ref, t_vec *vec_ref);

/* safe_str.c */
char		*safe_strdup(t_ctx *c_ref, const char *s);
char		*safe_strndup(t_ctx *c_ref, const char *s, size_t n);

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

/* toklst.c */
void		toklst_clear(t_ctx *c_ref, t_lst *toklst_ref);

#endif // LIB_H
