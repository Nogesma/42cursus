/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:48:54 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:48:56 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	free_list(char **lst)
{
	int	i;

	i = -1;
	while (lst[++i])
		free(lst[i]);
	free(lst);
}

void	print_list_fd(int fd, char *prefix, t_list *lst)
{
	while (lst)
	{
		ft_printf(fd, "%s%s\n", prefix, lst->content);
		lst = lst->next;
	}
}

t_list	*new_lst(t_list **head, t_list *elem, void *content)
{
	if (!(*head))
	{
		*head = ft_lstnew(content);
		elem = *head;
	}
	else
	{
		elem->next = ft_lstnew(content);
		elem = elem->next;
	}
	return (elem);
}

t_list	**char_to_lst(char **args)
{
	t_list	**head;
	t_list	*elem;
	char	*content;
	int		i;

	if (!args)
		return (NULL);
	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	*head = NULL;
	i = -1;
	while (args[++i])
	{
		content = ft_strdup(args[i]);
		if (!content)
		{
			ft_lstclear(head, free);
			free(head);
			return (NULL);
		}
		elem = new_lst(head, elem, content);
	}
	return (head);
}

char	**lst_to_char(t_list *head)
{
	char	**lst;
	int		i;

	lst = (char **) malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!lst)
		return (NULL);
	i = 0;
	while (head)
	{
		lst[i++] = head->content;
		head = head->next;
	}
	lst[i] = 0;
	return (lst);
}
