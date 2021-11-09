/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:24:42 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/09 15:24:44 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "quicksort.h"

int main(int argc, char **argv)
{
	int *arr;
	int i;
	int length;

	if (argc < 2)
		return (1);
	arr = (int *)malloc((argc - 1) * sizeof(int));
	length = argc - 1;
	i = -1;
	while (++i < length)
		arr[i] = ft_atoi(argv[i + 1]);
	i = -1;
//	ft_printf("Size of array: %d\n", length);
//	while (++i < length)
//		ft_printf("%d: %d\n", i, arr[i]);
	quicksort(arr, 0, length - 1);
	i = -1;
//	ft_printf("Sorted array:\n");
//	while (++i < length)
//		ft_printf("%d: %d\n", i, arr[i]);

}