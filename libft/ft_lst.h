/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 13:44:57 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 17:26:54 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H
# include <stddef.h>
# include <stdbool.h>

typedef struct s_lst	t_lst;

struct s_lst
{
	void		*data;
	t_lst		*next;
	t_lst		*prev;
};

/* ft_lst.c */
t_lst	ft_lst_make(void);
void	ft_lst_clear(t_lst *lst_ref);
void	ft_lst_clear_with(t_lst *lst_ref, void (*del)(void *));
size_t	ft_lst_size(const t_lst *lst_ref);
t_lst	*ft_lst_node_new(void *data);

/* ft_lst2.c */
bool	ft_lst_is_empty(const t_lst *lst_ref);
t_lst	*ft_lst_first(t_lst *lst_ref);
t_lst	*ft_lst_last(t_lst *lst_ref);
bool	ft_lst_is_first(const t_lst *lst_ref, const t_lst *nod_ref);
bool	ft_lst_is_last(const t_lst *lst_ref, const t_lst *nod_ref);

/* ft_lst_mut.c */
int		ft_lst_insert(t_lst *nod_ref, void *data);
void	ft_lst_remove(t_lst *nod_ref);
void	ft_lst_remove_with(t_lst *nod_ref, void (*del)(void *));

/* ft_lst_mut2.c */
int		ft_lst_push_front(t_lst *lst_ref, void *data);
int		ft_lst_push(t_lst *lst_ref, void *data);
void	*ft_lst_pop_front(t_lst *lst_ref);
void	*ft_lst_pop(t_lst *lst_ref);

#endif // LST_H
