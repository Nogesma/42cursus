/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:05:10 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/09 18:05:13 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void	echo(char **args)
{
	int	newline;

	newline = 1;
    if (!*args)
        return ;
    if (!ft_strncmp("-n", args[0], 3))
	{
		newline = 0;
		args++;
	}
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		if (*(args + 1))
			ft_putchar_fd(' ', 1);
		args++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}

void	unset(char **args, t_list **env)
{
	int	i;

	i = -1;
	while (args[++i])
		free_env(env, args[i]);
}

void	export(char **args, t_list **env)
{
	int		i;
	t_list	*new;
	char	*content;

	i = -1;
	while (args[++i])
	{
		content = ft_strdup(args[i]);
		if (!content)
		{
			mem_error();
			return ;
		}
		new = ft_lstnew(content, 1);
		if (!new)
		{
			free(content);
			mem_error();
			return ;
		}
		ft_lstadd_front(env, new);
	}
}

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
}

void	cd(char **args)
{
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd("minish: cd: ", 2);
		perror(args[1]);
	}
}

void	exit_cmd(char **args)
{
	int				i;

	ft_putendl_fd("exit", 2);
	if (*args == NULL)
		exit(0);
	i = -1;
	while (args[0][++i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			ft_putstr_fd("minish: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
	}
	if (args[1] != NULL)
		return (ft_putendl_fd("minish: exit: too many arguments", 2));
	i = (unsigned char) ft_atoi(args[0]);
	exit(i);
}

void	mem_error(void)
{
	ft_putendl_fd("mem alloc error: couldnt complete task", 2);
}
