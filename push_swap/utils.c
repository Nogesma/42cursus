/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:24:18 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 19:24:21 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_sorted(t_list *lst, int n)
{
	int	i;

	i = -1;
	while (++i < n && lst && lst->next)
	{
		if (lst->content > lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	ft_lstfind(t_list *lst, int n)
{
	int	i;

	if (!lst)
		return (-1);
	i = 0;
	while (lst)
	{
		if (lst->content == n)
			return (i);
		i++;
		lst = lst->next;
	}
	return (-1);
}

int	get_closest_index(t_list *lst, int *sorted, int start, int end)
{
	int	lindex;
	int	mindex;
	int	lstsize;

	mindex = -1;
	lstsize = ft_lstsize(lst);
	while (start < end)
	{
		lindex = ft_lstfind(lst, sorted[start]);
		if (lindex != -1 && (mindex == -1
				|| min(mindex, lstsize - mindex)
				> min(lindex, lstsize - lindex)))
			mindex = lindex;
		start++;
	}
	return (mindex);
}

int	get_interval(t_list *lst, int n, int *split, int *sorted)
{
	int	i;
	int	minindex;

	i = 0;
	minindex = -1;
	while (minindex == -1)
		minindex = ft_lstfind(lst, sorted[i++]);
	i--;
	if (i + *split > n)
		*split = n - i;
	return (i);
}

void	rotate(t_list **head, char *s, int i, void f(t_list **))
{
	while (i > 0)
	{
		ft_printf("%s\n", s);
		f(head);
		i--;
	}
}
