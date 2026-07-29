/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 12:39:34 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/29 16:58:43 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#define LL_MAX "9223372036854775807"
#define LL_MIN "9223372036854775808"

static bool	_is_numeric(const char *s)
{
	if (!s || !*s)
		return (false);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (false);
	while (*s && *s == ' ')
		s++;
	while (*s)
	{
		if (*s == ' ')
			break ;
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	while (*s)
	{
		if (*s != ' ')
			return (false);
		s++;
	}
	return (true);
}

static bool	_has_ll_overflow(const char *s)
{
	int		sign;
	int		len;

	sign = 1;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == '0')
		s++;
	len = 0;
	while (ft_isdigit(s[len]))
		len++;
	if (len > 19)
		return (true);
	if (len < 19)
		return (false);
	if (sign == -1)
		return (ft_strncmp(s, LL_MIN, 19) > 0);
	return (ft_strncmp(s, LL_MAX, 19) > 0);
}

static int	_exit_atoi(const char *s)
{
	unsigned long long	val;
	int					sign;

	val = 0;
	sign = 1;
	while (*s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		val = val * 10 + (*s - '0');
		s++;
	}
	if (sign == -1)
		return ((int)(-(long long)val));
	return ((int)val);
}

static void	_exit_numeric_error(t_ctx *c_ref, const char *arg)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	util_puterr("minishell: exit: ");
	util_puterr(arg);
	util_puterr(": numeric argument required\n");
	ctx_clear(c_ref);
	exit(2);
}

/*
	DESCIPTION
		- exit

	NOTE
		- 모든 경우 exit 출력 후 다음 동작 진행
		- `exit`: exit(0)
		- `exit 2`: exit(2)
		- `exit 1 2`, `exit 1 a`: `minishell: exit: too many arguments`, 1 return
		- `exit a`, `exit a 1`, `exit a b`:
			`minishell: exit: a: numeric argument required`, exit(2)
*/
int	cmd_built_exit(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	t_lst	*arg_node;
	char	*arg;
	int		ret;

	if (ft_lst_size(&cmd_ref->arglst) == 1)
	{
		ret = c_ref->status;
	}
	else
	{
		arg_node = cmd_ref->arglst.next->next;
		arg = arg_node->data;
		if (!_is_numeric(arg) || _has_ll_overflow(arg))
			_exit_numeric_error(c_ref, arg);
		if (arg_node->next != &cmd_ref->arglst)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			util_puterr("minishell: exit: too many arguments\n");
			return (1);
		}
		ret = _exit_atoi(arg);
	}
	ctx_clear(c_ref);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit((unsigned char)ret);
}
