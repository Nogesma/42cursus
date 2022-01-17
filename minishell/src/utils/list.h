/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:48:57 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:48:58 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <libft.h>

int		free_list(char **lst, int ret);

t_list	*new_lst(t_list **head, void *content);

t_list	**char_to_lst(char **args);

char	**lst_to_char(t_list *head);

#endif //LIST_H
