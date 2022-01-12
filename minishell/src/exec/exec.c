/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:47:34 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:47:39 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#include "../built-in/cd.h"
#include "../built-in/echo.h"
#include "../built-in/env.h"
#include "../built-in/exit.h"
#include "../built-in/export.h"
#include "../built-in/pwd.h"
#include "../built-in/unset.h"

#include "../utils/global.h"
#include "../utils/list.h"
#include "../utils/path.h"
#include "../utils/environ.h"

#include "../parser/parser.h"

int	exec_binary(char *path, char **args, t_list **env)
{
	pid_t	child;
	char	**environ;

	environ = lst_to_char(*env);
	child = fork();
	if (child == -1)
	{
		free(environ);
		return (0);
	}
	if (child == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(path);
			exit(127);
		}
	}
	is_fork(1, 1);
	free(environ);
	return (1);
}

int	fork_built_in(int (*fn)(char **, t_list **),
				char **a, t_list **b, char has_pipes)
{
	pid_t	child;
	int		ret;

	if (!has_pipes)
		ret = fn(a, b);
	child = fork();
	if (child == -1)
		return (2);
	if (child == 0)
	{
		if (!has_pipes)
			exit(ret);
		exit(fn(a, b));
	}
	is_fork(1, 1);
	return (1);
}

int	built_in(char **args, t_list **environ, char has_pipes)
{
	if (!ft_strncmp("cd", args[0], 3))
		return (fork_built_in(cd, args + 1, environ, has_pipes));
	if (!ft_strncmp("echo", args[0], 5))
		return (fork_built_in(echo, args + 1, environ, has_pipes));
	if (!ft_strncmp("pwd", args[0], 4))
		return (fork_built_in(pwd, args + 1, environ, has_pipes));
	if (!ft_strncmp("env", args[0], 4))
		return (fork_built_in(env, args + 1, environ, has_pipes));
	if (!ft_strncmp("unset", args[0], 6))
		return (fork_built_in(unset, args + 1, environ, has_pipes));
	if (!ft_strncmp("export", args[0], 7))
		return (fork_built_in(export, args + 1, environ, has_pipes));
	if (!ft_strncmp("exit", args[0], 5))
		return (fork_built_in(exit_cmd, args + 1, environ, has_pipes));
	return (0);
}

int	search_exec(char *line, t_list **env, char has_pipes)
{
	char	**args;
	char	*path;
	char	*command;
	int		ret;

	path = get_env_content(env, "PATH");
	args = ft_arg_split(line, env);
	ret = built_in(args, env, has_pipes);
	if (ret == 1)
		return (free_list(args, 1));
	else if (ret == 2)
		return (free_list(args, 0));
	command = args[0];
	if (!(line[0] == '.' || line[0] == '/'))
		args[0] = get_exec_path(args[0], path);
	if (args[0])
		ret = exec_binary(args[0], args, env);
	else
	{
		ft_printf(2, "minish: %s: command not found\n", command);
		status_code(1, 127);
		ret = 0;
	}
	if (!(line[0] == '.' || line[0] == '/'))
		free(command);
	return (free_list(args, ret));
}
