/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:24:22 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:24:23 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>
# include "math.h"

int		is_sorted(t_list *lst, int n);

int		ft_lstfind(t_list *lst, int n);

int		get_closest_index(t_list *lst, int *sorted, int start, int end);

int		get_interval(t_list *lst, int n, int *split, int *sorted);

void	rotate(t_list **head, char *s, int i, void f(t_list **));

#endif //UTILS_H
