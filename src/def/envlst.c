/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 16:02:59 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/28 15:48:17 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

static void	_copy_envlst_nodes(const t_lst *envlst_ref, t_lst **nodes)
{
	t_lst	*nod_ref;
	int		i;

	i = 0;
	nod_ref = envlst_ref->next;
	while (nod_ref && nod_ref != envlst_ref)
	{
		nodes[i++] = nod_ref;
		nod_ref = nod_ref->next;
	}
}

static void	_sort_envlst_nodes(t_lst **nodes, int count)
{
	int		i;
	int		j;
	t_lst	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(((t_env *)nodes[i]->data)->key,
					((t_env *)nodes[j]->data)->key) > 0)
			{
				tmp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = tmp;
			}
			j += 1;
		}
		i += 1;
	}
}

t_lst	**envlst_sort(t_ctx *c_ref, const t_lst *envlst_ref)
{
	t_lst	**nodes;
	int		count;

	count = ft_lst_size(envlst_ref);
	if (count == 0)
		return (0);
	nodes = safe_malloc(c_ref, sizeof(t_lst *) * count);
	_copy_envlst_nodes(envlst_ref, nodes);
	_sort_envlst_nodes(nodes, count);
	return (nodes);
}

static char	*env_to_str(t_ctx *c_ref, const t_env *env_ref)
{
	char	*str;
	char	*tmp;

	if (!env_ref->val)
		return (safe_strdup(c_ref, env_ref->key));
	tmp = safe_strjoin(c_ref, env_ref->key, "=");
	str = safe_strjoin(c_ref, tmp, env_ref->val);
	safe_free(c_ref, tmp);
	return (str);
}

char	**envlst_to_arr(t_ctx *c_ref, const t_lst *envlst_ref)
{
	char	**arr;
	int		i;
	t_lst	*nod_ref;

	arr = safe_malloc(c_ref,
			sizeof(char *) * (ft_lst_size(envlst_ref) + 1));
	i = 0;
	nod_ref = envlst_ref->next;
	while (nod_ref && nod_ref != envlst_ref)
	{
		arr[i] = env_to_str(c_ref, nod_ref->data);
		nod_ref = nod_ref->next;
		i += 1;
	}
	arr[i] = NULL;
	return (arr);
}
