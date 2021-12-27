/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:18:20 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/09 17:18:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(char **lst)
{
	int	i;

	i = -1;
	while (lst[++i])
		free(lst[i]);
	free(lst);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	str = (char *)ft_calloc(s1l + s2l + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1l + 1);
	str[s1l] = '/';
	ft_strlcpy(str + s1l + 1, s2, s2l + 1);
	return (str);
}

t_list	**char_to_lst(char **args)
{
	t_list	**head;
	t_list	*elem;
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
		if (!(*head))
		{
			*head = ft_lstnew(ft_strdup(args[i]));
			elem = *head;
		}
		else
		{
			elem->next = ft_lstnew(ft_strdup(args[i]));
			elem = elem->next;
		}
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

//todo remove debug
void	print_args_debug(char **args)
{
	printf("args:\n");
	while (*args)
	{
		printf("%s\n", *args);
		args++;
	}
	printf("end args\n");
}
