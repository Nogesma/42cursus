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

int	search_exec(char *line, t_list **env);

void	free_list(char **lst);

char	*ft_strjoin_path(char *s1, char *s2);

void	mem_error(void);

void	print_list(t_list *lst, char *prefix, int fd);

char	**ft_arg_split(char *s, t_list **env);

//env list
t_list	**char_to_lst(char **args);
char	**lst_to_char(t_list *head);
t_list	**free_env(t_list **head, char *name);
t_list	*get_env(t_list **env, char *name);
char	*get_env_content(t_list **env, char *name);

//built_ins
void	pwd(void);
void	export(char **args, t_list **env);
void	unset(char **args, t_list **env);
void	echo(char **args);
void	cd(char **args, t_list **env);
void	exit_cmd(char **args);

//debug
void	print_args_debug(char **args);

#endif //MINISHELL_H
