/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 11:49:05 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 11:54:28 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/**
 *	EXAMPLE
 *		./bin/session_parse_test echo hello
 *		MYVAR='ho hello' ./bin/session_parse_test ec$MYVAR
 *		MYVAR='ho hello' ./bin/session_parse_test "cmd \"\$MYVAR\""
 *		./bin/session_parse_test "cat < in.txt | grep hi >> out.txt"
 */
int	main(int argc, char **argv, char **envp)
{
	t_ctx		c;
	t_session	s;
	char		*input;

	if (argc < 2)
		return (0);
	input = tlib_join_args(argc, argv);
	ctx_init(&c, envp);
	s = session_make();
	s.input = safe_strdup(&c, input);
	if (session_parse(&c, &s) != ERROR_OK)
		logerr(&c);
	else
	{
		log_lst_with(&s.toklst, (void (*)(void *, size_t))log_token, 0, true);
		printf("\n");
	}
	free(input);
	session_clear(&c, &s);
	ctx_clear(&c);
	return (0);
}

