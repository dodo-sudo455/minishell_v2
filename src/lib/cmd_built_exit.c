/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:39:34 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/25 12:44:35 by doyelee          ###   ########.fr       */
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
	exit(1);
}

static void	_exit_too_many_exit(t_ctx *c_ref)
{
	printf("exit\n");
	write(2, "minishell: exit: too many arguments\n", 36);
	ctx_clear(c_ref);
	exit(1);
}

int	cmd_built_exit(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	t_lst	*arg_node;
	char	*arg;
	char	*second_arg;

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
		second_arg = arg_node->next->data;
		if (_exit_is_numeric(second_arg))
			return (_exit_too_many_args());
		_exit_too_many_exit(c_ref);
	}
	ctx_clear(c_ref);
	printf("exit\n");
	exit(ft_atoi(arg));
}
