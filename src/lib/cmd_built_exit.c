/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:39:34 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/25 13:39:30 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static bool	_exit_is_numeric(const char *s)
{
	if (!s || !*s)
		return (false);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	return (true);
}

static void	_exit_numeric_error(const char *arg, t_ctx *c_ref)
{
	printf("exit\n");
	write(2, "minishell: exit: ", 17);
	if (arg)
		write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	ctx_clear(c_ref);
	exit(2);
}

/*
	DESCIPTION
		- exit

	NOTE
		모든 경우 exit 출력 후 다음 동작 진행
		- `exit`: exit(0)
		- `exit 2`: exit(2)
		- `exit 1 2`: `minishell: exit: too many arguments` 출력, 1 return
		- `exit a`, `exit a 1`, `exit a b`: `minishell: exit: a: numeric argument required` 출력 후 exit(2)
		- `exit 1 a`: `minishell: exit: too many arguments` 출력, 1 return
*/
int	cmd_built_exit(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	t_lst	*arg_node;
	char	*arg;

	if (ft_lst_size(&cmd_ref->arglst) == 1)
	{
		ctx_clear(c_ref);
		printf("exit\n");
		exit(0);
	}
	arg_node = cmd_ref->arglst.next;
	arg = arg_node->data;
	if (!_exit_is_numeric(arg))
		_exit_numeric_error(arg, c_ref);
	if (arg_node->next != &cmd_ref->arglst)
	{
		printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	ctx_clear(c_ref);
	printf("exit\n");
	exit(ft_atoi(arg));
}
