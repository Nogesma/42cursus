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
#include "utils/utils.h"
#include "setup.h"

void	print_list(t_list *lst, char *prefix, int fd)
{
	while (lst)
	{
		ft_printf(fd, "%s%s\n", prefix, lst->content);
		lst = lst->next;
	}
}

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

int	is_built_in(char **args, t_list **environ)
{
	if (!ft_strncmp("pwd", args[0], 4))
		pwd();
	else if (!ft_strncmp("cd", args[0], 3))
		cd(args + 1, environ);
	else if (!ft_strncmp("env", args[0], 4))
	{
		print_list(*environ, "", STDOUT_FILENO);
		status_code(1, 0);
	}
	else if (!ft_strncmp("echo", args[0], 5))
		echo(args + 1);
	else if (!ft_strncmp("unset", args[0], 6))
		unset(args + 1, environ);
	else if (!ft_strncmp("export", args[0], 7))
		export(args + 1, environ);
	else if (!ft_strncmp("exit", args[0], 5))
		exit_cmd(args + 1);
	else
		return (0);
	return (1);
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

	len = ft_strlen(exec);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_type != DT_DIR && !ft_strncmp(exec, dp->d_name, len))
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

	paths = ft_split(PATH, ':');
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

	//todo recursive token analysis and execution
	path = get_env_content(env, "PATH");
	args = ft_arg_split(line, env); //testing " ' and $ expansion
	if (is_built_in(args, env) == 1)
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
void	sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		status_code(1, 130);
	}
	if (!is_fork(0, 0))
		rl_on_new_line();
	rl_redisplay();
}

int	main(__attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av,
		char **env)
{
	char	prompt[9];
	int		ret;
	char	*line;
	t_list	**environ;

	ret = termios_setup();
	if (ret < 0)
		return (-1);
	if (ret != STDIN_FILENO)
		prompt[0] = 0;
	else
		ft_strlcpy(prompt, "minish$ ", 9);
	environ = char_to_lst(env);
	if (!environ)
		return (1);
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
	line = readline(prompt);
	while (line)
	{
		if (*line)
		{
			add_history(line);
			//todo cleanup_tokens()
			search_exec(line, environ);
		}
		free(line);
		line = readline(prompt);
	}
}
