/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:37:06 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 14:37:08 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void	bubble_sort(char **lst)
{
	int	i;
	int	j;

	i = 0;
	while (lst[++i])
	{
		j = 0;
		while (lst[++j])
		{
			if (ft_strncmp(lst[j], lst[j - 1], ft_strlen(lst[j]) + 1) < 0)
				ft_swap(&lst[j], &lst[j - 1]);
		}
	}
}
