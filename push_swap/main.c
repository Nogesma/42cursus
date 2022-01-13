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
	int		n;
	int		length;
	t_list	*elem;

	n = 0;
	if (argc == 2)
	{
		n = -1;
		argv = ft_split(argv[1], ' ');
		argc = 0;
		while (argv[argc])
			argc++;
		length = argc;
	}
	else
		length = argc - 1;
	while (--argc > n)
	{
		elem = ft_lstnew(ft_atoi(argv[argc]));
		if (!elem)
			return (0);
		ft_lstadd_front(head, elem);
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
	if (length == 0)
	{
		free_all(head_a, NULL);
		return (1);
	}
	sort(head_a, length);
}
