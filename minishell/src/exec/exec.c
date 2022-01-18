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
#include "../parser/rec_mult.h"
#include "pipes.h"

void	mpipe(int fdi[2], int fdo[2])
{
//	ft_printf(2, "%d %d\n%d %d\n", fdi[0],fdi[1],fdo[0],fdo[1]);
	if (fdo[0] != fdo[1])
	{
		close(fdo[0]);
		dup2(fdo[1], STDOUT_FILENO);
	}
	if (fdi[0] != fdi[1])
	{
		close(fdi[1]);
		dup2(fdi[0], STDIN_FILENO);
	}
}

int	exec_binary(char *path, char **args, t_list **env, int fdi[2], int fdo[2])
{
	pid_t	child;
	char	**environ;

	environ = lst_to_char(*env);
	if (!environ)
		return (0);
	status_code(1, 0);
	child = fork();
	if (child == -1)
	{
		free(environ);
		return (0);
	}
	if (child == 0)
	{
		mpipe(fdi, fdo);
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
				char **a, t_list **b, int fdi[2], int fdo[2])
{
	pid_t	child;
	int		ret;

	ret = 0;
	status_code(1, 0);
	if (fdo[0] == fdo[1] && fdi[0] == fdi[1])
	{
		if (fn == exit_cmd)
			ret = fn(a, NULL);
		else
			ret = fn(a, b);
	}
	child = fork();
	if (child == -1)
		return (0);
	if (child == 0)
	{
		mpipe(fdi, fdo);
		if (fdo[0] == fdo[1] && fdi[0] == fdi[1])
			exit(ret);
		exit(fn(a, b));
	}
	is_fork(1, 1);
	return (1);
}

int	built_in(char **args, t_list **environ, int fdi[2], int fdo[2])
{
	if (!ft_strncmp("cd", args[0], 3))
		return (fork_built_in(cd, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("echo", args[0], 5))
		return (fork_built_in(echo, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("pwd", args[0], 4))
		return (fork_built_in(pwd, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("env", args[0], 4))
		return (fork_built_in(env, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("unset", args[0], 6))
		return (fork_built_in(unset, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("export", args[0], 7))
		return (fork_built_in(export, args + 1, environ, fdi, fdo));
	if (!ft_strncmp("exit", args[0], 5))
		return (fork_built_in(exit_cmd, args + 1, environ, fdi, fdo));
	return (-1);
}

int	cmd_err(char *command)
{
	if (!(command[0] == '.' || command[0] == '/'))
		ft_printf(STDERR_FILENO,
			"minishell: %s: command not found\n", command);
	else
		ft_printf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", command);
	status_code(1, 127);
	return (0);
}

int	search_exec(char *line, t_list **env, int fdi[2], int fdo[2])
{
	char	**args;
	char	*path;
	char	*command;
	int		ret;

	args = ft_arg_split(line, env);
	if (!args || !(*args))
		return (0);
	ret = built_in(args, env, fdi, fdo);
	if (ret != -1)
		return (free_list(args, ret));
	path = get_env_content(env, "PATH");
	if (!path)
		return (free_list(args, 0));
	command = args[0];
	if (!(line[0] == '.' || line[0] == '/'))
		command = get_exec_path(args[0], path);
	if (command)
		ret = exec_binary(command, args, env, fdi, fdo);
	else
		ret = cmd_err(args[0]);
	if (command && command != args[0])
		free(command);
	return (free_list(args, ret));
}
