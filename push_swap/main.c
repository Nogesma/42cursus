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

#include <libft.h>
#include "sort.h"

int	create_list(t_list **head, int argc, char **argv)
{
	int	i;
	int	length;

	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		i = 0;
		while (argv[i])
			i++;
		length = i;
		while (i-- > 0)
			ft_lstadd_front(head, ft_lstnew(ft_atoi(argv[i])));
	}
	else
	{
		length = argc - 1;
		i = length;
		while (i-- > 0)
			ft_lstadd_front(head, ft_lstnew(ft_atoi(argv[i + 1])));
	}
	return (length);
}

int	main(int argc, char **argv)
{
	t_list	**head_a;
	int		length;

	if (argc < 2)
		return (1);
	head_a = (t_list **)malloc(sizeof(t_list *));
	if (!head_a)
	{
		free(head_a);
		return (1);
	}
	length = create_list(head_a, argc, argv);
	sort(head_a, length);
}
