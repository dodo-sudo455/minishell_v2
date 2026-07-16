/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:20:07 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 14:59:51 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H
# include <stdbool.h>
# include <signal.h>
# include "libft.h"

typedef struct s_ctx		t_ctx;
typedef struct s_env		t_env;
typedef enum e_error		t_error;

/* ---------------------------------- */
/* ctx                                */
/* ---------------------------------- */

/**
 *	DESCRIPTION
 *
 *		 This struct holds reused data including session data
 *		and maintains address list for implementing garbage
 *		collector.
 *		 The garbage collector is implemented in `memlst`, which
 *		is a list of dynamically 
 *		 B/c the garbage collector itself is a list, `memlst`
 *		uses raw api from `libft.h`.  Other lists will use
 *		safe functions in `lib.h`.
 *
 *	TODO
 *		- handle heredoc list
 */
struct s_ctx
{
	char		**envp;
	t_lst		envlst;

	t_lst		memlst;
};

t_ctx		ctx_make(void);
void		ctx_init(t_ctx *c_ref, char **envp);
void		ctx_clear(t_ctx *c_ref);
void		ctx_session_clear(t_ctx *c_ref);
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
/* error                              */
/* ---------------------------------- */

enum e_error
{
	ERROR_OK,
	ERROR_INTERNAL,
	ERROR_DEBUG,
	ERROR_SYN,
};

/* ---------------------------------- */
/* panic                              */
/* ---------------------------------- */

void		panic(t_ctx *c_ref, t_error err, const char *s);

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
int			safe_vec_push(t_ctx *c_ref, t_vec *vec_ref, char c);
int			safe_vec_push_n(t_ctx *c_ref,
				t_vec *vec_ref, const char *buf, size_t n);
char		*safe_vec_to_str(t_ctx *c_ref, t_vec *vec_ref);

#endif // DEF_H
