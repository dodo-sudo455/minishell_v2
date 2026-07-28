/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 13:30:00 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 16:10:35 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <fcntl.h>
#include <unistd.h>

size_t	util_envlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	if (s[0] == '\0')
		return (0);
	if (ft_isalpha((unsigned char)s[0]) == 0 && s[0] != '_')
		return (0);
	i = 1;
	while (ft_isalnum((unsigned char)s[i]) || s[i] == '_')
		i += 1;
	return (i);
}

ssize_t	util_puterr(const char *s)
{
	return (write(STDERR_FILENO, s, ft_strlen(s)));
}

int	util_parse_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

char	**util_lst_to_arr(t_ctx *c_ref, const t_lst *arglst_ref)
{
	char		**argv;
	const t_lst	*p;
	size_t		i;

	argv = safe_malloc(c_ref,
			sizeof(char *) * (ft_lst_size(arglst_ref) + 1));
	p = arglst_ref->next;
	i = 0;
	while (p && p != arglst_ref)
	{
		argv[i] = safe_strdup(c_ref, (char *)p->data);
		p = p->next;
		i += 1;
	}
	argv[i] = NULL;
	return (argv);
}
