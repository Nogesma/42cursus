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

void	exec_binary(char *path, char **args, t_list **env)
{
	pid_t	child;
	char	**environ;

	environ = lst_to_char(*env);
	child = fork();
	if (child == -1)
		return (free(environ));
	if (child == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(path);
			exit(1);
		}
	}
	is_fork(1, 1);
	free(environ);
}

void	fork_built_in(int (*fn)(char **, t_list **),
				char **a, t_list **b, char has_pipes)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		return ;
	if (child == 0)
	{
		if (!has_pipes && fn == exit_cmd)
			exit(1);
		if (fn(a, b) == -1)
			exit(1);
	}
	is_fork(1, 1);
	if (!has_pipes)
		fn(a, 0);
}

int	built_in(char **args, t_list **environ, char has_pipes)
{
	if (!ft_strncmp("cd", args[0], 3))
		fork_built_in(cd, args + 1, environ, 1);
	else if (!ft_strncmp("echo", args[0], 5))
		fork_built_in(echo, args + 1, environ, 1);
	else if (!ft_strncmp("pwd", args[0], 4))
		fork_built_in(pwd, args + 1, environ, 1);
	else if (!ft_strncmp("env", args[0], 4))
		fork_built_in(env, args + 1, environ, 1);
	else if (!ft_strncmp("unset", args[0], 6))
		fork_built_in(unset, args + 1, environ, 1);
	else if (!ft_strncmp("export", args[0], 7))
		fork_built_in(export, args + 1, environ, 1);
	else if (!ft_strncmp("exit", args[0], 5))
		fork_built_in(exit_cmd, args + 1, environ, has_pipes);
	else
		return (0);
	return (1);
}

void	search_exec(char *line, t_list **env, char has_pipes)
{
	char	**args;
	char	*path;
	char	*command;

	path = get_env_content(env, "PATH");
	args = ft_arg_split(line, env);
	if (built_in(args, env, has_pipes) == 1)
		return (free_list(args));
	command = args[0];
	if (!(line[0] == '.' || line[0] == '/'))
		args[0] = get_exec_path(args[0], path);
	if (args[0])
		exec_binary(args[0], args, env);
	else
	{
		ft_putstr_fd("minish: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (!(line[0] == '.' || line[0] == '/'))
		free(command);
	free_list(args);
}
