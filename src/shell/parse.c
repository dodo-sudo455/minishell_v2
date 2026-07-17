/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:16:30 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/17 14:09:23 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	parse(t_ctx *c_ref, const char *input, t_lst *toklst_ref)
{
	if (!parse_is_quote_ok(input))
		return (false);
	parse_tokenize(c_ref, input, toklst_ref);
	parse_expand(c_ref, toklst_ref);
	parse_quote(c_ref, toklst_ref);
	return (true);
}
