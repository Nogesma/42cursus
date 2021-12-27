/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:18 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/01 13:06:20 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>

# include "built_ins/built_ins.h"

void	free_list(char **lst);

char	*ft_strjoin_path(char *s1, char *s2);

char	**ft_arg_split(char *s, t_list **env);

//env list
t_list	**char_to_lst(char **args);
char	**lst_to_char(t_list *head);

//debug
void	print_args_debug(char **args);

//sort
void	bubble_sort(char **lst);

#endif //MINISHELL_H
