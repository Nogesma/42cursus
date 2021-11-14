/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:41:14 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 18:41:19 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Mano Segransan on 11/14/21.
//

#include "math.h"

int	ft_sqrt(int nb)
{
	long	i;
	long	p;

	i = 0;
	p = 0;
	while (p <= nb)
	{
		if (p > nb)
			return ((int)i);
		++i;
		p = i * i;
	}
	return ((int)i);
}

int	lstmin(t_list *lst)
{
	int	i;
	int	j;
	int	min;

	i = 0;
	j = 0;
	min = lst->content;
	while (lst)
	{
		if (lst->content < min)
		{
			min = lst->content;
			j = i;
		}
		i++;
		lst = lst->next;
	}
	return (j);
}

int	lstmax(t_list *lst)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = lst->content;
	while (lst)
	{
		if (lst->content > max)
		{
			max = lst->content;
			j = i;
		}
		i++;
		lst = lst->next;
	}
	return (j);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
