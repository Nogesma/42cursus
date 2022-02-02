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
#include "../utils/error.h"

#include "../parser/parser.h"
#include "../parser/cmd_loop.h"
#include "../utils/pipes.h"

/**
 * Forks the main process and execute fd redirection if needed
 * then execute the command path with args.
 * **/
static int	exec_binary(char *path, char **args, t_list **env, t_pipe *fd)
{
	pid_t	child;
	char	**environ;

	environ = lst_to_char(*env);
	if (!environ)
		return (0);
	status_code(1, 0);
	child = fork();
	if (child == -1)
		free(environ);
	if (child == -1)
		return (0);
	if (child == 0)
	{
		if (mpipe(fd))
			exit(1);
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

static int	exec_built_in(int (*fn)(char **, t_list **),
				char **a, t_list **b, t_pipe *fd)
{
	int	saved_fd[2];
	int	ret;

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	if (mpipe(fd))
		return (1);
	if (fn == exit_cmd)
		ret = fn(a, NULL);
	else
		ret = fn(a, b);
	restore_fd(fd, saved_fd);
	return (ret);
}

/**
 * Forks the main process and execute fd redirection if needed
 * then execute the built-in command with args.
 * **/
static int	fork_built_in(int (*fn)(char **, t_list **),
				char **a, t_list **b, t_pipe *fd)
{
	pid_t	child;
	int		ret;

	ret = 0;
	status_code(1, 0);
	if (fd->token != 2)
		ret = exec_built_in(fn, a, b, fd);
	child = fork();
	if (child == -1)
		return (0);
	if (child == 0)
	{
		if (fd->token != 2)
			exit(ret);
		if (mpipe(fd))
			exit(1);
		exit(fn(a, b));
	}
	is_fork(1, 1);
	return (1);
}

/**
 * Checks if the command is a built-in, if it is, executes it.
 * **/
static int	built_in(char **args, t_list **environ, t_pipe *fd)
{
	if (!ft_strncmp("cd", args[0], 3))
		return (fork_built_in(cd, args + 1, environ, fd));
	if (!ft_strncmp("echo", args[0], 5))
		return (fork_built_in(echo, args + 1, environ, fd));
	if (!ft_strncmp("pwd", args[0], 4))
		return (fork_built_in(pwd, args + 1, environ, fd));
	if (!ft_strncmp("env", args[0], 4))
		return (fork_built_in(env, args + 1, environ, fd));
	if (!ft_strncmp("unset", args[0], 6))
		return (fork_built_in(unset, args + 1, environ, fd));
	if (!ft_strncmp("export", args[0], 7))
		return (fork_built_in(export, args + 1, environ, fd));
	if (!ft_strncmp("exit", args[0], 5))
		return (fork_built_in(exit_cmd, args + 1, environ, fd));
	return (-1);
}

/**
 * Checks if a command exists and execute it.
 * **/
int	search_exec(char *line, t_list **env, t_pipe *fd)
{
	char	**args;
	char	*path;
	char	*command;
	int		ret;

	args = ft_arg_split(line, env);
	if (!args || !(*args))
		return (0);
	ret = built_in(args, env, fd);
	if (ret != -1)
		return (free_list(args, ret));
	path = get_env_content(env, "PATH");
	command = args[0];
	if (!(line[0] == '.' || line[0] == '/'))
		command = get_exec_path(args[0], path);
	if (command)
		ret = exec_binary(command, args, env, fd);
	else
		ret = cmd_err(args[0]);
	if (command && command != args[0])
		free(command);
	return (free_list(args, ret));
}
