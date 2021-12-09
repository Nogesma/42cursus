//
// Created by Tadeusz Kondracki on 12/2/21.
//

#include "minishell.h"

static void	print_list(t_list *lst)
{
	while(lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

int	echo(char **args)
{
	int	newline;

	newline = 1;
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
	return (1);
}

int	unset(char **args, t_list **env)
{
	int	i;

	i = -1;
	while (args[++i])
		free_env(env, args[i]);
	return (1);
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


int	env(t_list **environ)
{
	print_list(*environ);
	return (1);
}

int	pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
}

int	cd(char **args)
{
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd("minish: cd: ", 2);
		perror(args[1]);
	}
	return (1);
}

void	mem_error(void)
{
	ft_putendl_fd("mem alloc error: couldnt complete task", 2);
}
