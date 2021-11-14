/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:26:29 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:26:30 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_BIG_H
# define SORT_BIG_H

# include <libft.h>
# include "stack.h"
# include "utils.h"
# include "bubble_sort.h"

void	split(t_list **head_a, t_list **head_b, int div);

void	solve(t_list **head_a, t_list **head_b);

#endif //SORT_BIG_H
