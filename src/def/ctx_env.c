/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyelee <doyelee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:37:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 14:02:48 by doyelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"
#include <stddef.h>

char	*ctx_getenv(t_ctx *c_ref, const char *key)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	nod_ref = c_ref->envlst.next;
	while (nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		if (ft_strcmp(env_ref->key, key) == 0)
			return (safe_strdup(c_ref, env_ref->val));
		nod_ref = nod_ref->next;
	}
	return (safe_strdup(c_ref, ""));
}

/**
 *	DESCRIPTION
 *
 *		 If `key` exists in `c_ref.envlst`, update with `val`.
 *		Else, push a new entry.
 */
void	ctx_setenv(t_ctx *c_ref, const char *key, const char *val)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	nod_ref = c_ref->envlst.next;
	while (nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		if (ft_strcmp(env_ref->key, key) == 0)
		{
			if (env_ref->val)
				safe_free(c_ref, env_ref->val);
			env_ref->val = safe_strdup(c_ref, val);
			return ;
		}
		nod_ref = nod_ref->next;
	}
	env_ref = safe_malloc(c_ref, sizeof(t_env));
	env_ref->key = safe_strdup(c_ref, key);
	env_ref->val = safe_strdup(c_ref, val);
	safe_lst_push(c_ref, &c_ref->envlst, env_ref);
}

static void	_safe_drop_env(t_ctx *c_ref, void *data)
{
	env_drop(c_ref, data);
}

void	ctx_unsetenv(t_ctx *c_ref, const char *key)
{
	t_lst	*nod_ref;
	t_env	*env_ref;

	nod_ref = c_ref->envlst.next;
	while (nod_ref != &c_ref->envlst)
	{
		env_ref = nod_ref->data;
		if (ft_strcmp(env_ref->key, key) == 0)
		{
			safe_lst_remove_with(c_ref, nod_ref, _safe_drop_env);
			break ;
		}
		nod_ref = nod_ref->next;
	}
}

void	ctx_setstatus(t_ctx *c_ref, int stat)
{
	c_ref->status = stat;
}
