#include "minishell.h"
#include <libft.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>

void exec_binary(char *path, char **args, char **env)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
		return ;
	if (child == 0)
	{
		if (execve(path, args, env) == -1)
		{
//			printf("errno: %d, %s", errno, strerror(errno));
			return ;
		}
	}
//	printf("normal errno: %d, %s", errno, strerror(errno));
	if (child > 0)
		wait(&status);
}

// TODO: check if line exec build int shell command, and exec built in
int	is_built_in(const char *line)
{
	(void)line;
	return (0);
}

void print_list(char **lst)
{
	for (int i = 0; lst[i]; i++)
	{
		printf("%s\n", lst[i]);
	}
}

void free_list(char **lst)
{
	int	i;

	i = -1;
	while(lst[++i])
		free(lst[i]);
	free(lst);
}

char *search_path(char *path, char *exec)
{
	DIR *dir;
	struct dirent *dp;
	struct stat statbuf;
	size_t len;
	char *exec_path;

	len = ft_strlen(exec);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_type == DT_DIR && ft_strncmp(".", dp->d_name, 1))
		{
//			ft_printf("DIR--> path: %s\nname: %s\n", path, dp->d_name);
			// TODO: create function to join paths with / between

			/** Careful, memory leak in strjoin below **/
			exec_path = ft_strjoin(path, "/");
			exec_path = ft_strjoin(exec_path, dp->d_name);
			path = exec_path;
//			ft_printf("DIR--> path: %s\n", path);
//			ft_printf("%p\n", &dp);
			exec_path = search_path(path, exec);
			if (exec_path)
				return (exec_path);
		}
		else if (dp->d_namlen == len && !ft_strncmp(exec, dp->d_name, len))
		{
//			ft_printf("FILENAME--> path: %s\nname: %s\n", path, dp->d_name);
			// TODO: create function to join paths with / between

			/** Careful, memory leak in strjoin below **/
			exec_path = ft_strjoin(path, "/");
			exec_path = ft_strjoin(exec_path, exec);
			if (stat(exec_path, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
				return (exec_path);
		}
//		else
//			ft_printf("FILE--> path: %s\nname: %s\n", path, dp->d_name);
		dp = readdir(dir);
	}
	return (NULL);
}

char *get_exec_path(char *exec, char *PATH)
{
	char **paths;
	int i;
	char *exec_path;

	paths = ft_split(&PATH[5], ':');
	i = -1;
	exec_path = NULL;
	while (paths[++i] && exec_path == NULL)
		exec_path = search_path(paths[i], exec);
//	ft_printf("i: %d ", i);
//	ft_printf("PATH: %s\nexec_path: %s\nexec: %s.\n", paths[i], exec_path, exec);
	return (exec_path);
}

char *get_env(char **env, char *name)
{
	int i;
	size_t len;

	len = ft_strlen(name);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(name, env[i], len))
			return (env[i]);
	return (NULL);
}

void search_exec(char *line, char **env)
{
	char **args;
	char *PATH;

	PATH = get_env(env, "PATH");
	args = ft_split(line, ' ');
	if (is_built_in(line))
		return ;
	if (!(line[0] == '.' || line[0] == '/'))
		args[0] = get_exec_path(args[0], PATH);
	if (args[0])
	{
		exec_binary(args[0], args, env);
	}
	free_list(args);
}


void sigint(__attribute__ ((unused)) int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_forced_update_display();
}

int	main(__attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;

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
