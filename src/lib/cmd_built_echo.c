/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 20:13:28 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/25 13:34:33 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*
	DESCRIPTION
		- echo의 n 옵션을 확인

	RETURN VALUE
		- `-n`, `-nn`, `-nnnnnnn...` 모두 true 반환
		- `-ni` 등은 false 반환
*/
static bool	_is_n_option(const char *s)
{
	if (!s || *s != '-')
		return (false);
	s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (*s != 'n')
			return (false);
		s++;
	}
	return (true);
}

/*
	DESCRIPTION
		- echo 뒤의 인자를 출력
		- `-n` 옵션 시 맨 끝 줄바꿈 문자 출력하지 않음

	NOTE
		- `echo` -> 줄바꿈만 출력
		- `echo hello` -> hello 출력 후 줄바꿈 출력
		- `echo -n hello` -> hello만 출력
		- `echo -nnnnn hello` -> `echo -n hello`와 같음
		- `echo -na hello` -> -na hello 출력 후 줄바꿈 출력
		- `echo hi -n hello` -> hi -n hello 출력 후 줄바꿈 출력
*/
int	cmd_built_echo(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	bool	is_n_opt;
	t_lst	*arglst;

	is_n_opt = false;
	arglst = cmd_ref->arglst.next;
	if (arglst != &cmd_ref->arglst && _is_n_option(arglst->data))
	{
		is_n_opt = true;
		arglst = arglst->next;
	}
	while (arglst != &cmd_ref->arglst)
	{
		printf("%s", arglst->data);
		if (arglst->next != &cmd_ref->arglst)
			printf(" ");
		arglst = arglst->next;
	}
	if (!is_n_opt)
		printf("\n");
	return (0);
}
