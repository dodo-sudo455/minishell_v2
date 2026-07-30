/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 20:13:28 by doyelee           #+#    #+#             */
/*   Updated: 2026/07/30 14:10:32 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/**
 *	DESCRIPTION
 *
 *		- Check for the n option in echo
 *
 *	RETURN VALUE
 *		- Return true for `-n`, `-nn`, `-nnnnnnn...`
 *		- Return false for `-ni`, etc.
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
		- Print arguments following echo
		- Do not print a trailing newline if `-n` option is provided

	NOTE
		- `echo` -> Print only a newline
		- `echo hello` -> Print hello followed by a newline
		- `echo -n hello` -> Print only hello
		- `echo -nnnnn hello` -> Same as `echo -n hello`
		- `echo -na hello` -> Print -na hello followed by a newline
		- `echo hi -n hello` -> Print hi -n hello followed by a newline
*/
int	cmd_built_echo(t_ctx *c_ref, const t_cmd *cmd_ref)
{
	bool	is_n_opt;
	t_lst	*arglst;

	(void)c_ref;
	is_n_opt = false;
	arglst = cmd_ref->arglst.next;
	if (arglst != &cmd_ref->arglst)
		arglst = arglst->next;
	while (arglst != &cmd_ref->arglst && _is_n_option(arglst->data))
	{
		is_n_opt = true;
		arglst = arglst->next;
	}
	while (arglst != &cmd_ref->arglst)
	{
		ft_putstr_fd((char *)arglst->data, STDOUT_FILENO);
		if (arglst->next != &cmd_ref->arglst)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arglst = arglst->next;
	}
	if (!is_n_opt)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
