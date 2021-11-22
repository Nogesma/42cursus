#include "minishell.h"
#include <libft.h>
#include <signal.h>

void search_relative(char *line)
{
	extern char *const environ[];
	char **const command = ft_split(line, ' ');
	ft_printf("%s\n", getcwd(NULL, 0));
	execve(line, command, environ);
}

void search_exec(char *line)
{
	if (line[0] == '.' || line[0] == '/')
		search_relative(line);
//	search_path(line)
}

void newline()
{
	char *line;

	line = readline("minish$ ");
	while (line)
	{
		if (*line)
		{
			add_history(line);
			search_exec(line);
		}
		free(line);
		line = readline("minish$ ");
	}
}

void sigint(__attribute__ ((unused)) int sig)
{
	write(1, "\n", 1);
	newline();
}

int	main(void)
{
	signal(SIGINT, sigint);
	newline();
}