#include "minishell.h"

char	*get_env(t_list **env, char *name)
{
	t_list	*elem;
	size_t	len;

	len = ft_strlen(name);
	elem = *env;
	while (elem)
	{
		if (!ft_strncmp(name, elem->content, len))
			return (elem->content);
		elem = elem->next;
	}
	return (NULL);
}

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

t_list **char_to_lst(char **args)
{
	t_list **head;
	t_list *elem;
	int i;

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
			*head = ft_lstnew(args[i], 0);
			elem = *head;
		}
		else
		{
			elem->next = ft_lstnew(args[i], 0);
			elem = elem->next;
		}
	}
	return (head);
}

char **lst_to_char(t_list *head)
{
	char **lst;
	int i;

	lst = (char **) malloc(sizeof(char *) * ft_lstsize(head));
	if (!lst)
		return (NULL);
	i = 0;
	while (head)
	{
		lst[i++] = head->content;
		head = head->next;
	}
	return (lst);
}

t_list **free_env(t_list **head, char *name)
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
			ft_lstdelone(elem, free);
			return (head);
		}
		prev = elem;
		elem = elem->next;
	}
	return (head);
}
