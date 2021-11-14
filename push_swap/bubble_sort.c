/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:14:37 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 17:14:42 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

static int	is_sorted(const int *list, int list_size)
{
	int	i;

	i = -1;
	while (++i < list_size - 1)
		if (list[i] > list[i + 1])
			return (0);
	return (1);
}

void	bubble_sort(int *list, int list_size)
{
	int	j;

	while (!is_sorted(list, list_size))
	{
		j = -1;
		while (++j < list_size - 1)
			if (list[j] > list[j + 1])
				ft_swap(&list[j], &list[j + 1]);
	}
}
