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
#include <libft.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>

void	free_list(char **lst);

char	*ft_strjoin_path(char *s1, char *s2);

void	mem_error(void);

//env list
t_list	**char_to_lst(char **args);
char	**lst_to_char(t_list *head);
t_list	**free_env(t_list **head, char *name);
char	*get_env(t_list **env, char *name);

//built_ins
int		pwd();
int		env(t_list **environ);
void	export(char **args, t_list **env);
int		unset(char **args, t_list **env);
int		echo();
int		cd(char **args);


#endif //MINISHELL_H
