/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 18:41:03 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 17:06:00 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <readline/readline.h>
#include <readline/history.h>

void	*safe_malloc(t_ctx *c_ref, size_t size)
{
	void	*p;

	p = gc_malloc(&c_ref->gc, size);
	if (!p)
		panic(c_ref, ERROR_INTERNAL, NULL);
	return (p);
}

void	safe_free(t_ctx *c_ref, void *p)
{
	gc_free(&c_ref->gc, p);
}

char	*safe_readline(t_ctx *c_ref, const char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input && gc_push(&c_ref->gc, input) != 0)
	{
		free(input);
		panic(c_ref, ERROR_INTERNAL, NULL);
	}
	return (input);
}
