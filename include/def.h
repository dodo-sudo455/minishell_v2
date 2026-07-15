/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:20:07 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 17:23:00 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H
# include <stdbool.h>
# include "libft.h"

typedef struct s_ctx		t_ctx;
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
 *		 B/c the garbage collector itself is a list, `memlst`
 *		uses raw api from `libft.h`. Other lists will use
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

t_ctx	ctx_make(void);
void	ctx_init(t_ctx *c_ref, char **envp);
void	ctx_clear(t_ctx *c_ref);
void	ctx_session_clear(t_ctx *c_ref);

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

#endif // DEF_H
