/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:19:17 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:19:19 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	brute_force3(t_list *lst)
{
	if (lstmin(lst) == 0)
	{
		ft_printf("sa\n");
		ft_printf("ra\n");
	}
	else if (lstmin(lst) == 1)
	{
		if (lstmax(lst) == 0)
			ft_printf("ra\n");
		else
			ft_printf("sa\n");
	}
	else
	{
		if (lstmax(lst) == 1)
			ft_printf("rra\n");
		else
		{
			ft_printf("sa\n");
			ft_printf("rra\n");
		}
	}
}

void	free_all(t_list **a, t_list **b)
{
	ft_lstclear(b);
	free(b);
	ft_lstclear(a);
	free(a);
}

void	sort(t_list **head_a, int n)
{
	t_list	**head_b;

	if (is_sorted(*head_a, n))
		return ;
	if (n <= 3)
		return (brute_force3(*head_a));
	head_b = (t_list **)malloc(sizeof(t_list *));
	if (!head_b)
		return (free_all(head_a, head_b));
	(*head_b) = 0;
	if (n <= 5)
		sort5(head_a, head_b);
	else if (n <= 76)
	{
		split(head_a, head_b, 3);
		solve(head_a, head_b);
	}
	else
	{
		split(head_a, head_b, (int)(ft_sqrt(n) / 2.5));
		solve(head_a, head_b);
	}
	return (free_all(head_a, head_b));
}
