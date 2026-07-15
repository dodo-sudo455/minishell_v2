/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:59:25 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/15 15:59:55 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "def.h"
# include "lib.h"

/* ---------------------------------- */
/* exec                               */
/* ---------------------------------- */

t_error		exec(t_ctx *c_ref, const t_lst *toklst_ref, t_lst *cmdlst_ref);
void		exec_parse(t_ctx *c_ref,
				const t_lst *toklst_ref, t_lst *cmdlst_ref);
t_error		exec_redir(t_ctx *c_ref, t_lst *cmdlst_ref);
t_error		exec_pipe(t_ctx *c_ref, t_lst *cmdlst_ref);
t_error		exec_run(t_ctx*c_ref, t_lst *cmdlst_ref);

#endif // MAIN_H
