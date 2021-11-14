/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:26:54 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/14 17:26:56 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bubble_sort.h"
#include <stdlib.h>
#include "median.h"

static int	*clone_list(t_list *src, int n)
{
	int	*dest;
	int	i;

	dest = (int *)malloc((n) * sizeof(int));
	i = -1;
	while (++i < n && src)
	{
		dest[i] = src->content;
		src = src->next;
	}
	return (dest);
}

int	get_median_value(t_list *lst, int n)
{
	int	*sort;
	int	i;

	if (n < 3 && lst)
		return (lst->content);
	sort = clone_list(lst, n);
	bubble_sort(sort, n);
	i = sort[n / 2];
	free(sort);
	return (i);
}

int	*get_sorted(t_list *lst, int n)
{
	int	*sort;

	sort = clone_list(lst, n);
	bubble_sort(sort, n);
	return (sort);
}
