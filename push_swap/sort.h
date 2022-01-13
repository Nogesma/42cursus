/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:19:21 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:19:23 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <libft.h>
# include "sort_big.h"
# include "sort5.h"

void	sort(t_list **head_a, int n);

void	free_all(t_list **a, t_list **b);

#endif //SORT_H
