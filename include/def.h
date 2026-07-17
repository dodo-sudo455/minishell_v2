/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:20:07 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 15:16:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H
# include <stdbool.h>
# include <signal.h>
# include "libft.h"

typedef struct s_ctx		t_ctx;
typedef struct s_env		t_env;
typedef enum e_fatal		t_fatal;
typedef t_lst				t_gc;

/* ---------------------------------- */
/* ctx                                */
/* ---------------------------------- */

/**
 *	DESCRIPTION
 *
 *		 This struct holds reused data including session data
 *		and maintains address list for implementing garbage
 *		collector.
 *
 *	TODO
 *		- handle heredoc list
 */
struct s_ctx
{
	t_gc		gc;
	char		**envp;
	t_lst		envlst;
};

/* ctx.c */
t_ctx		ctx_make(void);
void		ctx_init(t_ctx *c_ref, char **envp);
void		ctx_clear(t_ctx *c_ref);
void		ctx_session_clear(t_ctx *c_ref);

/* ctx_doc.c */
void		ctx_doclst_push(t_ctx *c_ref, const char *fname);
void		ctx_doclst_clear(t_ctx *c_ref);

/* ctx_env */
char		*ctx_getenv(t_ctx *c_ref, const char *key);
void		ctx_expand(t_ctx *c_ref, char **s);

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

/* ---------------------------------- */
/* fatal                              */
/* ---------------------------------- */

enum e_fatal
{
	FATAL_OK,
	FATAL_INTERNAL,
	FATAL_DEBUG,
	FATAL_EXIT,
};

/* ---------------------------------- */
/* gc                                 */
/* ---------------------------------- */

t_gc		gc_make(void);
int			gc_push(t_gc *gc_ref, void *p);
void		*gc_malloc(t_gc *gc_ref, size_t size);
void		gc_free(t_gc *gc_ref, void *p);
void		gc_clear(t_gc *gc_ref);

/* ---------------------------------- */
/* panic                              */
/* ---------------------------------- */

void		panic(t_ctx *c_ref, t_fatal err, const char *errparam);

/* ---------------------------------- */
/* safe                               */
/* ---------------------------------- */

/* safe.c */
void		*safe_malloc(t_ctx *c_ref, size_t size);
void		safe_free(t_ctx *c_ref, void *p);
char		*safe_readline(t_ctx *c_ref, const char *prompt);

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

/* safe_sig.c */
void		safe_sigemptyset(t_ctx *c_ref, sigset_t *set);
void		safe_sigaction(t_ctx *c_ref, int signum,
				const struct sigaction *act, struct sigaction *oldact);

/* safe_str.c */
char		*safe_strdup(t_ctx *c_ref, const char *s);
char		*safe_strndup(t_ctx *c_ref, const char *s, size_t n);

/* safe_vec.c */
void		safe_vec_clear(t_ctx *c_ref, t_vec *vec_ref);
void		safe_vec_push(t_ctx *c_ref, t_vec *vec_ref, char c);
void		safe_vec_push_n(t_ctx *c_ref,
				t_vec *vec_ref, const char *buf, size_t n);
char		*safe_vec_to_str(t_ctx *c_ref, t_vec *vec_ref);

#endif // DEF_H
