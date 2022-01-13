/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:15:25 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 17:15:29 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUBBLE_SORT_H
# define BUBBLE_SORT_H

# include <libft.h>

int		*get_sorted(t_list *lst, int n);

void	ft_swap(int *a, int *b);

#endif //BUBBLE_SORT_H
