/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:19:54 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 18:50:10 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static inline bool	_is_space(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n');
}

static inline bool	_is_meta(char c)
{
	return (c == '<'
		|| c == '>'
		|| c == '|');
}

/**
 *	DESCRIPTION
 *
 *		 Suppose the quote syntax is validated from the
 *		previous step. There must be a pair of quotes.
 */
static size_t	_count_word_len(const char *input, size_t start)
{
	size_t	i;

	i = start;
	while (input[i] && !_is_space(input[i]) && !_is_meta(input[i]))
	{
		if (input[i] == '\'')
		{
			i += 1;
			while (input[i] != '\'')
				i += 1;
			i += 1;
		}
		else if (input[i] == '"')
		{
			i += 1;
			while (input[i] != '"')
				i += 1;
			i += 1;
		}
		else
			i += 1;
	}
	return (i - start);
}

static size_t	_count_token_len(const char *input, size_t i)
{
	if (input[i] == '|')
		return (1);
	if (ft_strncmp(input + i, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(input + i, ">>", 2) == 0)
		return (2);
	if (input[i] == '<')
		return (1);
	if (input[i] == '>')
		return (1);
	return (_count_word_len(input, i));
}

/**
 *	DESCRIPTION
 *
 *		 Parse the input string and store tokens in `toklst_ref`.
 *		Meta characters (e.g. '<', '<<', '|') should also be tokenized.
 */
void	parse_tokenize(t_ctx *c_ref, const char *input, t_lst *toklst_ref)
{
	size_t	i;
	size_t	toklen;
	t_token	*tok_ref;

	*toklst_ref = ft_lst_make();
	i = 0;
	while (input[i])
	{
		if (_is_space(input[i]))
		{
			i += 1;
			continue ;
		}
		toklen = _count_token_len(input, i);
		tok_ref = token_new(c_ref, safe_strndup(c_ref, input + i, toklen));
		safe_lst_push(c_ref, toklst_ref, tok_ref);
		i += toklen;
	}
}
