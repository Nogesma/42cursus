/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:36:16 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 17:36:18 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	rotate_stack(t_list **stack)
{
	t_list	*temp;

	ft_lstlast(*stack)->next = *stack;
	temp = (*stack)->next;
	(*stack)->next = NULL;
	*stack = temp;
}

void	rotate_reverse_stack(t_list **stack)
{
	t_list	*temp;

	temp = *stack;
	if (!temp)
		return ;
	while (temp && temp->next && temp->next->next)
		temp = temp->next;
	temp->next->next = *stack;
	*stack = temp->next;
	temp->next = NULL;
}

void	push_stack(t_list **head_a, t_list **head_b)
{
	t_list	*temp;

	temp = *head_a;
	if (temp)
	{
		*head_a = temp->next;
		temp->next = *head_b;
		*head_b = temp;
	}
}

void	swap_stack(t_list **head_a)
{
	t_list	*temp;

	temp = (*head_a)->next;
	(*head_a)->next = temp->next;
	temp->next = *head_a;
	*head_a = temp;
}

void	rollback(t_list **head, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		rotate_reverse_stack(head);
}
