/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:07:05 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:07:07 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

static t_list	**free_env(t_list **head, char *name)
{
	t_list	*elem;
	t_list	*prev;
	size_t	len;

	len = ft_strlen(name);
	elem = *head;
	prev = *head;
	while (elem)
	{
		if (!ft_strncmp(name, elem->content, len)
			&& ((char *)elem->content)[len] == '=')
		{
			prev->next = elem->next;
			if (elem == *head)
				*head = elem->next;
			ft_lstdelone(elem, free);
			return (head);
		}
		prev = elem;
		elem = elem->next;
	}
	return (head);
}

int	unset(char **args, t_list **env)
{
	int	i;

	i = -1;
	while (args[++i])
		free_env(env, args[i]);
	return (0);
}
