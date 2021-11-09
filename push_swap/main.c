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
	t_list **head_a;
	t_list **head_b;
	int i;
	int length;

	if (argc < 2)
		return (1);
	length = argc - 1;
	i = length;
	head_a = (t_list **)malloc(sizeof(t_list *));
	head_b = (t_list **)malloc(sizeof(t_list *));
	(*head_a) = 0;
	(*head_b) = 0;
	while (i-- > 0)
		ft_lstadd_front(head_a,ft_lstnew(ft_atoi(argv[i + 1])));
	quicksort(head_a, head_b, length - 1, 0);
}