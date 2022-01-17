/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:35:38 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "utils/setup.h"
#include "utils/global.h"
#include "utils/list.h"
#include "parser/rec_mult.h"
#include "parser/validator.h"

void	sig(__attribute__ ((unused)) int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	status_code(1, 130);
	if (!is_fork(0, 0))
		rl_on_new_line();
	rl_redisplay();
}

void	readline_loop(t_list **environ, char *prompt)
{
	char	*line;

	line = readline(prompt);
	while (line)
	{
		if (*line)
		{
			add_history(line);
			if (!check_line(line))
				cmds_loop(line, environ);
		}
		free(line);
		line = readline(prompt);
	}
}

// TODO: Put both our name in all headers if possible
int	main(__attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av,
			char **env)
{
	char	prompt[9];
	int		ret;
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
	signal(SIGQUIT, SIG_IGN);
	readline_loop(environ, prompt);
	rl_clear_history();
	ft_lstclear(environ, free);
	free(environ);
	return (1);
}
