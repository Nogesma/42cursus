#include <libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "utils/setup.h"
#include "utils/global.h"
#include "utils/list.h"
#include "exec/exec.h"

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
	rl_clear_history();
	ft_lstclear(environ, free);
	free(environ);
}
