/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:26:26 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:26:28 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_big.h"

void rotate_both(t_list **head_a, t_list **head_b, int *lindex, int r)
{
	int	lstsize;

	if (r == 0)
		return ;
	lstsize = ft_lstsize(*head_a);
	if (*lindex <= lstsize / 2 && *lindex > 0)
	{
		ft_printf("rr\n");
		rotate_stack(head_a);
		rotate_stack(head_b);
		(*lindex)--;
	}
	else
	{
		ft_printf("rb\n");
		rotate_stack(head_b);
	}
}

void	put_stack(t_list **head_a, t_list **head_b, int lindex, int r)
{
	int	lstsize;

	rotate_both(head_a, head_b, &lindex, r);
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
	push_stack(head_a, head_b);
	ft_printf("pb\n");
	if ((*head_b) && (*head_b)->next && (*head_b)->content < (*head_b)->next->content)
	{
		ft_printf("sb\n");
		lstsize = (*head_b)->content;
		(*head_b)->content = (*head_b)->next->content;
		(*head_b)->next->content = lstsize;
	}
}

int	is_closer(int a, int b, int size)
{
	if (b != -1 && (a == -1 || min(a, size - a) > min(b, size - b)))
		return (1);
	return (0);
}

void	put_b(t_list **head_a, t_list **head_b, int div, int *sorted)
{
	int	split;
	int	n;
	int	li;
	int	ri;
	int	rr;

	n = ft_lstsize(*head_a);
	split = n / div;
	rr = 0;
	while (ft_lstsize(*head_a) > 0)
	{
		ri = get_interval(*head_a, n, &split, sorted);
		li = get_closest_index(*head_a, sorted, ri, ri + split / 2);
		ri = get_closest_index(*head_a, sorted, ri + split / 2, ri + split);
		if (is_closer(li, ri, ft_lstsize(*head_a)))
		{
			put_stack(head_a, head_b, ri, rr);
			rr = 1;
		}
		else
		{
			put_stack(head_a, head_b, li, rr);
			rr = 0;
		}
	}
}

void	split(t_list **head_a, t_list **head_b, int div)
{
	int	i;
	int	*sorted;

	sorted = get_sorted(*head_a, ft_lstsize(*head_a));
	if (!sorted)
		return ;
	i = -1;
	while (++i <= div)
		put_b(head_a, head_b, div, sorted);
}

void	solve(t_list **head_a, t_list **head_b)
{
	int	n;
	int	i;
	int	*sorted;

	n = ft_lstsize(*head_b) - 1;
	sorted = get_sorted(*head_b, n + 1);
	if (!sorted)
		return ;
	ft_printf("pa\n");
	push_stack(head_b, head_a);
	while ((*head_a)->content != sorted[0])
	{
		if ((*head_b)->content < (*head_a)->content)
		{
			ft_printf("pa\n");
			push_stack(head_b, head_a);
		}
		else
		{
			ft_printf("rb\n");
			rotate_stack(head_b);
		}
	}
	int j = 0;
	while (ft_lstsize(*head_b) != 0)
	{
		if ((*head_b)->content < (*head_a)->content && (*head_b)->content > ft_lstlast(*head_a)->content)
		{
			ft_printf("pa\n");
			push_stack(head_b, head_a);
		}
//		if ((*head_b)->content > lstmax(*head_a) && lstmin(*head_a) == (*head_a)->content)
//		{
//			ft_printf("pa\n");
//			push_stack(head_b, head_a);
//		}
		else
		{
			if ((*head_b)->content > (*head_a)->content)
			{
				ft_printf("ra\n");
				rotate_stack(head_a);
			}
			else
			{
				ft_printf("rra\n");
				rotate_reverse_stack(head_a);
			}
			if (j++ == 100000)
				return ;
		}
	}
//	while (n > -1)
//	{
//		i = ft_lstfind(*head_b, sorted[n]);
//		if (i <= n / 2)
//			rotate(head_b, "rb", i, rotate_stack);
//		else
//			rotate(head_b, "rrb", n + 1 - i, rotate_reverse_stack);
//		ft_printf("pa\n");
//		push_stack(head_b, head_a);
//		n--;
//	}
}
