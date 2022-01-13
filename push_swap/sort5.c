/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:19:32 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:19:34 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort5.h"

static int	iss(t_list **head)
{
	int		j;
	t_list	*lst;

	j = -1;
	while (++j < ft_lstsize(*head))
	{
		lst = *head;
		while (lst && lst->next)
		{
			if (lst->content > lst->next->content)
				break ;
			lst = lst->next;
		}
		if (!lst->next)
		{
			rollback(head, j);
			return (1);
		}
		rotate_stack(head);
	}
	rollback(head, j);
	return (0);
}

static void	put5(t_list **head_a, t_list **head_b, int lindex)
{
	int	lstsize;

	lstsize = ft_lstsize(*head_a);
	if (lindex <= lstsize / 2)
	{
		while (lindex > 0)
		{
			ft_printf("ra\n");
			rotate_stack(head_a);
			lindex--;
		}
	}
	else
	{
		while (lindex != lstsize)
		{
			ft_printf("rra\n");
			rotate_reverse_stack(head_a);
			lindex++;
		}
	}
	ft_printf("pa\n");
	push_stack(head_b, head_a);
}

static void	insert(t_list **head_a, t_list **head_b, int *sorted, int n)
{
	int	i;
	int	lindex;
	int	gindex;

	i = 0;
	while (i < n && sorted[i] != (*head_b)->content)
		i++;
	if (i != 0)
		lindex = ft_lstfind(*head_a, sorted[i - 1]);
	else
		lindex = ft_lstfind(*head_a, sorted[n - 1]);
	if (i != n - 1)
		gindex = ft_lstfind(*head_a, sorted[i + 1]);
	else
		gindex = ft_lstfind(*head_a, sorted[0]);
	if (lindex != -1)
		put5(head_a, head_b, lindex + 1);
	else if (gindex != -1)
		put5(head_a, head_b, gindex);
}

void	sort5(t_list **head_a, t_list **head_b)
{
	int	lstsize;
	int	*sorted;

	lstsize = ft_lstsize(*head_a);
	sorted = get_sorted(*head_a, lstsize);
	if (!sorted)
		return ;
	while (!iss(head_a) && ft_lstsize(*head_b) != 2)
	{
		ft_printf("pb\n");
		push_stack(head_a, head_b);
	}
	if (!iss(head_a))
	{
		ft_printf("sa\n");
		swap_stack(head_a);
	}
	while (ft_lstsize(*head_b) != 0)
		insert(head_a, head_b, sorted, lstsize);
	if (lstmin(*head_a) <= ft_lstsize(*head_a) / 2)
		rotate(head_a, "ra", lstmin(*head_a), rotate_stack);
	else
		rotate(head_a, "rra", ft_lstsize(*head_a)
			- lstmin(*head_a), rotate_stack);
}
