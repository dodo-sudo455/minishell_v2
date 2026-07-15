/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 13:48:48 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/12 17:26:54 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H
# include <stddef.h>

typedef struct s_vec	t_vec;

struct s_vec
{
	char	*arr;
	size_t	len;
	size_t	cap;
};

t_vec	ft_vec_make(size_t cap);
void	ft_vec_clear(t_vec *vec_ref);
int		ft_vec_push(t_vec *vec_ref, char c);
int		ft_vec_push_n(t_vec *vec_ref, const char *buf, size_t n);
char	*ft_vec_to_str(t_vec *vec_ref);

#endif // FT_VEC_H
