/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:36:26 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 17:36:28 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <libft.h>

void	rotate_stack(t_list **stack);

void	rotate_reverse_stack(t_list **stack);

void	push_stack(t_list **head_a, t_list **head_b);

#endif //STACK_H
