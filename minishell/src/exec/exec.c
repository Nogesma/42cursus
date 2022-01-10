//
// Created by segransm on 1/10/22.
//

#include <libft.h>
#include <stdio.h>
#include <sys/wait.h>

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
	int		status;

	environ = lst_to_char(*env);
	status_code(1, 0);
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
	wait(&status);
	is_fork(1, 0);
	if (status_code(0, 0) != 130 && WIFEXITED(status))
		status_code(1, WEXITSTATUS(status));
	free(environ);
}

int	built_in(char **args, t_list **environ)
{
	int	ret;

	if (!ft_strncmp("cd", args[0], 3))
		ret = cd(args + 1, environ);
	else if (!ft_strncmp("echo", args[0], 5))
		ret = echo(args + 1);
	else if (!ft_strncmp("pwd", args[0], 4))
		ret = pwd();
	else if (!ft_strncmp("env", args[0], 4))
		ret = env(*environ);
	else if (!ft_strncmp("unset", args[0], 6))
		ret = unset(args + 1, environ);
	else if (!ft_strncmp("export", args[0], 7))
		ret = export(args + 1, environ);
	else if (!ft_strncmp("exit", args[0], 5))
		ret = exit_cmd(args + 1);
	else
		return (0);
	status_code(1, ret);
	return (1);
}

void	search_exec(char *line, t_list **env)
{
	char	**args;
	char	*path;
	char	*command;

	//todo recursive token analysis and execution
	path = get_env_content(env, "PATH");
	args = ft_arg_split(line, env); //testing " ' and $ expansion
	if (built_in(args, env) == 1)
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
