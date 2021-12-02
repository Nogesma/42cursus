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

void	exec_binary(char *path, char **args, char **env)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child == -1)
		return ;
	if (child == 0 && execve(path, args, env) == -1)
	{
		perror(path);
		exit(1);
	}
	if (child > 0)
		wait(&status);
}

// TODO: check if line exec build int shell command, and exec built in
int	is_built_in(const char *line)
{
	(void)line;
	return (0);
}

void	print_list(char **lst)
{
	for (int i = 0; lst[i]; i++)
	{
		printf("%s\n", lst[i]);
	}
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

void	search_exec(char *line, char **env)
{
	char	**args;
	char	*path;
	char	*command;

	if (is_built_in(line))
		return ;
	path = get_env(env, "PATH");
	args = ft_split(line, ' ');
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

	signal(SIGINT, sigint);
	line = readline("minish$ ");
	while (line)
	{
		if (*line)
		{
			add_history(line);
			search_exec(line, env);
		}
		free(line);
		line = readline("minish$ ");
	}
}
