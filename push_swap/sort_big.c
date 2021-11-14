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

void	put_stack(t_list **head_a, t_list **head_b, int lindex)
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
	ft_printf("pb\n");
	push_stack(head_a, head_b);
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

	n = ft_lstsize(*head_a);
	split = n / div;
	while (ft_lstsize(*head_a) > 0)
	{
		ri = get_interval(*head_a, n, &split, sorted);
		li = get_closest_index(*head_a, sorted, ri, ri + split / 2);
		ri = get_closest_index(*head_a, sorted, ri + split / 2, ri + split);
		if (is_closer(li, ri, ft_lstsize(*head_a)))
		{
			put_stack(head_a, head_b, ri);
			ft_printf("rb\n");
			rotate_stack(head_b);
		}
		else
			put_stack(head_a, head_b, li);
	}
}

void	split(t_list **head_a, t_list **head_b, int div)
{
	int	i;
	int	*sorted;

	sorted = get_sorted(*head_a, ft_lstsize(*head_a));
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
	while (n > -1)
	{
		i = ft_lstfind(*head_b, sorted[n]);
		if (i <= n / 2)
			rotate(head_b, "rb", i, rotate_stack);
		else
			rotate(head_b, "rrb", n + 1 - i, rotate_reverse_stack);
		ft_printf("pa\n");
		push_stack(head_b, head_a);
		n--;
	}
}
