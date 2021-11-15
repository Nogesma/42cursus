#include "minishell.h"

int	main(void)
{
	char *line;
	line = readline("minish$ ");
	while (line)
	{
		free(line);
		line = readline("minish$ ");
	}
}