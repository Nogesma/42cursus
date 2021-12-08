/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:06:12 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/01 13:06:14 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_binary(char *path, char **args, t_list **env)
{
	pid_t	child;
	char **environ;
	int		status;

	child = fork();
	if (child == -1)
		return ;
	environ = lst_to_char(*env);
	if (child == 0 && execve(path, args, environ) == -1)
	{
		free(environ);
		perror(path);
		exit(1);
	}
	free(environ);
	if (child > 0)
		wait(&status);
}

int	is_built_in(char **args, t_list **environ)
{
	if (!ft_strncmp("pwd", args[0], 4))
		return (pwd());
	if (!ft_strncmp("cd", args[0], 3))
		return (cd(args + 1));
	if (!ft_strncmp("env", args[0], 4))
		return (env(environ));
	if (!ft_strncmp("echo", args[0], 5))
		return (echo(args + 1));
	if (!ft_strncmp("unset", args[0], 6))
		return (unset(environ));
	if (!ft_strncmp("export", args[0], 7))
		return (export(environ));
	if (!ft_strncmp("exit", args[0], 5))
		exit(0);
	return (0);
}

char	*free_path_search(char *s, DIR *dir)
{
	closedir(dir);
	return (s);
}

char	*search_path(char *path, char *exec)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		statbuf;
	size_t			len;
	char			*exec_path;
	char			*temp;

	len = ft_strlen(exec);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_type == DT_DIR && ft_strncmp(".", dp->d_name, 1))
		{
			temp = ft_strjoin_path(path, dp->d_name);
			exec_path = search_path(temp, exec);
			free(temp);
			if (exec_path)
				return (free_path_search(exec_path, dir));
		}
		else if (dp->d_namlen == len && !ft_strncmp(exec, dp->d_name, len))
		{
			exec_path = ft_strjoin_path(path, exec);
			if (stat(exec_path, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
				return (free_path_search(exec_path, dir));
		}
		dp = readdir(dir);
	}
	return (free_path_search(NULL, dir));
}

char	*get_exec_path(char *exec, char *PATH)
{
	char	**paths;
	int		i;
	char	*exec_path;

	paths = ft_split(&PATH[5], ':');
	i = -1;
	exec_path = NULL;
	while (paths[++i] && exec_path == NULL)
		exec_path = search_path(paths[i], exec);
	free_list(paths);
	return (exec_path);
}

void	search_exec(char *line, t_list **env)
{
	char	**args;
	char	*path;
	char	*command;

	path = get_env(env, "PATH=");
	args = ft_split(line, ' ');
	if (is_built_in(args, env))
		return ;
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
	if (!args[0])
		free(command);
	free_list(args);
}

// TODO: cat followed by a sigint displays two prompts without a newline
void	sigint(__attribute__ ((unused)) int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(__attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av,
		char **env)
{
	char	*line;
	t_list **environ;

	environ = char_to_lst(env);
	signal(SIGINT, sigint);
	line = readline("minish$ ");
	while (line)
	{
		if (*line)
		{
			add_history(line);
			search_exec(line, environ);
		}
		free(line);
		line = readline("minish$ ");
	}
}
