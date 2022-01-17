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

int	free_list(char **lst, int ret)
{
	int	i;

	i = -1;
	while (lst[++i])
		free(lst[i]);
	free(lst);
	return (ret);
}

void	print_list_fd(int fd, char *prefix, t_list *lst)
{
	while (lst)
	{
		ft_printf(fd, "%s%s\n", prefix, lst->content);
		lst = lst->next;
	}
}

int	new_lst(t_list **head, void *content)
{
	t_list	*elem;

	if (!content)
	{
		ft_lstclear(head, free);
		free(head);
		return (1);
	}
	elem = ft_lstnew(content);
	if (!elem)
	{
		ft_lstclear(head, free);
		free(head);
		return (1);
	}
	ft_lstadd_front(head, elem);
	return (0);
}

t_list	**char_to_lst(char **args)
{
	t_list	**head;
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
		if (new_lst(head, ft_strdup(args[i])))
			return (NULL);
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
