/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:23:56 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 14:58:38 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_env	*env_new(t_ctx *c_ref, const char *s)
{
	t_env	*env_ref;
	char	*pos;

	env_ref = safe_malloc(c_ref, sizeof(t_env));
	ft_memset(env_ref, 0, sizeof(t_env));
	pos = ft_strchr(s, '=');
	if (pos)
	{
		env_ref->key = safe_strndup(NULL, s, pos - s);
		env_ref->val = safe_strdup(NULL, pos + 1);
	}
	else
	{
		env_ref->key = safe_strdup(NULL, s);
		env_ref->val = NULL;
	}
	return (env_ref);
}

void	env_drop(t_ctx *c_ref, t_env *env_ref)
{
	if (!env_ref)
		return ;
	if (env_ref->key)
		safe_free(c_ref, env_ref->key);
	if (env_ref->val)
		safe_free(c_ref, env_ref->val);
	safe_free(c_ref, env_ref);
}

void	envlst_init(t_ctx *c_ref, t_lst *envlst_ref, char **envp)
{
	t_env	*env_ref;

	while (*envp)
	{
		env_ref = env_new(c_ref, *envp);
		safe_lst_push(c_ref, envlst_ref, env_ref);
		envp += 1;
	}
}

static void	_safe_drop_env(t_ctx *c_ref, void *data)
{
	env_drop(c_ref, (t_env *)data);
}

void	envlst_clear(t_ctx *c_ref, t_lst *envlst_ref)
{
	safe_lst_clear_with(c_ref, envlst_ref, _safe_drop_env);
}
