#ifndef LIST_H
# define LIST_H

#include <libft.h>

void	free_list(char **lst);

t_list	*new_lst(t_list **head, t_list *elem, void *content);

t_list	**char_to_lst(char **args);

char	**lst_to_char(t_list *head);

#endif //LIST_H
