/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:07:00 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:07:01 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>

#include "../utils/list.h"
#include "../utils/environ.h"
#include "../utils/sort.h"

static int	is_valid_env(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
	{
		ft_printf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", str);
		return (0);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_printf(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

static void	print_sorted_env(t_list **env)
{
	char	**lst;
	int		i;

	lst = lst_to_char(*env);
	if (!lst)
		return ;
	bubble_sort(lst);
	i = -1;
	while (lst[++i])
	{
		if (ft_strncmp(lst[i], "_=", 2))
			ft_printf(STDOUT_FILENO, "%s %s\n", "declare -x", lst[i]);
	}
	free(lst);
}

static void	mem_error(void *arg1)
{
	if (arg1)
		free(arg1);
	ft_printf(STDERR_FILENO, "mem alloc error: couldnt complete task");
}

void	add_env(t_list **env, char *content)
{
	t_list	*new;

	new = get_env(env, content);
	if (new)
	{
		free(new->content);
		new->content = content;
	}
	else
	{
		new = ft_lstnew(content);
		if (!new)
			return (mem_error(content));
		ft_lstadd_front(env, new);
	}
}

int	export(char **args, t_list **env)
{
	int		i;
	char	*content;

	i = -1;
	while (args[++i])
	{
		if (!is_valid_env(args[i]))
			continue ;
		content = ft_strdup(args[i]);
		if (!content)
		{
			mem_error(NULL);
			return (-1);
		}
		add_env(env, content);
	}
	if (i == 0)
		print_sorted_env(env);
	return (0);
}
