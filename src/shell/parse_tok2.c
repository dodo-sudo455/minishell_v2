/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 10:36:50 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 11:56:47 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	_token_drop(t_ctx *c_ref, void *data)
{
	token_drop(c_ref, (t_token *)data);
}

static bool	_has_quote(const char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (true);
		s += 1;
	}
	return (false);
}

/**
 *	DESCRIPTION
```
sp := _split_word(current_word)
current_token.update_with(sp[0])
for s in sp[1:] {
	current_node.insert()
}
```
 */
static void	_handle_word(t_ctx *c_ref, t_lst *nod_ref)
{
	t_lst		slst;
	t_token		*tok_ref;
	char		*s;
	t_lst		*insert_ref;

	tok_ref = nod_ref->data;
	slst = ft_lst_make();
	_parse_split_word(c_ref, tok_ref->s, &slst);
	if (ft_lst_is_empty(&slst))
	{
		safe_lst_remove_with(c_ref, nod_ref, _token_drop);
		return ;
	}
	s = safe_lst_pop_front(c_ref, &slst);
	safe_free(c_ref, tok_ref->s);
	tok_ref->s = s;
	tok_ref->has_quote = _has_quote(tok_ref->s);
	insert_ref = nod_ref;
	while (!ft_lst_is_empty(&slst))
	{
		s = safe_lst_pop_front(c_ref, &slst);
		insert_ref = safe_lst_insert(c_ref, insert_ref, token_new(c_ref, s));
	}
}

void	parse_split_word(t_ctx *c_ref, t_lst *toklst_ref)
{
	t_lst	*nod_ref;
	t_lst	*next_ref;
	t_token	*tok_ref;

	nod_ref = toklst_ref->next;
	while (nod_ref && nod_ref != toklst_ref)
	{
		next_ref = nod_ref->next;
		tok_ref = nod_ref->data;
		if (token_is_word(tok_ref))
			_handle_word(c_ref, nod_ref);
		nod_ref = next_ref;
	}
}
