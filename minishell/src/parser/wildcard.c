/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:30:41 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/12 15:30:43 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <libft.h>
#include <stdlib.h>
#include "../utils/sort.h"
#include "../utils/list.h"

int	count_wildcard(int is_wildcard)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	if (!is_wildcard)
		return (1);
	dir = opendir(".");
	if (!dir)
		return (0);
	dp = readdir(dir);
	i = 0;
	while (dp)
	{
		if (dp->d_name[0] != '.')
			i++;
		dp = readdir(dir);
	}
	closedir(dir);
	return (i);
}

static void	get_dir_content(t_list **lst)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	dir = opendir(".");
	if (!dir)
		return ;
	dp = readdir(dir);
	i = 0;
	while (dp)
	{
		if (dp->d_name[0] != '.')
		{
			if (new_lst(lst, ft_strdup(dp->d_name)))
				return ;
			i++;
		}
		dp = readdir(dir);
	}
	closedir(dir);
	bubble_sort_lst(lst, i);
}

char	*wildcard(int *pos)
{
	static t_list	**lst;
	t_list			*elem;
	char			*content;

	if (!lst)
	{
		lst = (t_list **)malloc(sizeof(t_list *));
		if (!lst)
			return (NULL);
		*lst = NULL;
		get_dir_content(lst);
	}
	elem = *lst;
	*lst = elem->next;
	content = elem->content;
	free(elem);
	if (!*lst)
	{
		free(lst);
		lst = NULL;
		(*pos)++;
	}
	return (content);
}
