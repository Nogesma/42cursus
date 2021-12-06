//
// Created by Tadeusz Kondracki on 12/2/21.
//

#include "minishell.h"

static void	print_list(char **lst)
{
	while(*lst)
	{
		ft_printf("%s\n", *lst);
		lst++;
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

int	unset()
{
	//todo
	return(1);
}

int	export()
{
	//todo
	return (1);
}


int	env(char **environ)
{
	print_list(environ);
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
