/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:37:55 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/21 15:13:46 by minseobk         ###   ########.fr       */
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

void	ctx_setstatus(t_ctx *c_ref, int stat)
{
	c_ref->status = stat;
}
