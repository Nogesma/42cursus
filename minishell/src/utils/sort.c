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

#include <libft.h>

static void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

/**
 * Does a bubble sort of the char array lst.
 * **/
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

static int	strncmp_insensitive(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] == '\0' || ft_tolower(s1[i]) != ft_tolower(s2[i]))
			return ((unsigned char)ft_tolower(s1[i])
				- (unsigned char)ft_tolower(s2[i]));
		++i;
	}
	--i;
	return ((unsigned char)ft_tolower(s1[i])
		- (unsigned char)ft_tolower(s2[i]));
}

/**
 * Does a bubble sort of the t_list lst. This function is used to sort
 * **/
void	bubble_sort_lst(t_list **lst, int size)
{
	int		i;
	t_list	*elem;

	i = 0;
	while (i < size)
	{
		elem = *lst;
		while (elem->next != NULL)
		{
			if (strncmp_insensitive(elem->content, elem->next->content,
					ft_strlen(elem->content) + 1) > 0)
				ft_swap((char **)&(elem->content),
					(char **)&(elem->next->content));
			elem = elem->next;
		}
		i++;
	}
}
