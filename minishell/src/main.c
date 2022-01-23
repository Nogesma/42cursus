/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:35:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 17:12:40 by msegrans         ###   ########.fr       */
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
#include "parser/cmd_loop.h"
#include "parser/syntax/validator.h"
#include "built-in/exit.h"

/** Called when user presses Ctrl-c, clears and redisplays prompt **/
void	sig(__attribute__ ((unused)) int sig)
{
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	status_code(1, 130);
	if (!is_fork(0, 0))
		rl_on_new_line();
	rl_redisplay();
}

/**
 * main loop where each line inputted by the user is received
 * using readline and then executed
 *  **/
void	readline_loop(t_list **environ, char *prompt)
{
	char	*line;
	int		forks;
	t_pipe	fd;

	line = readline(prompt);
	while (line)
	{
		if (*line)
		{
			add_history(line);
			if (!check_line(line))
			{
				fd.out[0] = STDOUT_FILENO;
				fd.out[1] = STDOUT_FILENO;
				fd.in[0] = STDIN_FILENO;
				fd.in[1] = STDIN_FILENO;
				forks = cmds_loop(line, environ, &fd);
				wait_forks(&forks);
			}
		}
		free(line);
		line = readline(prompt);
	}
}

void	cleanup_on_exit(t_list **environ)
{
	char	**exit_args;
	char	exit_code[2];

	rl_clear_history();
	ft_lstclear(environ, free);
	free(environ);
	ft_strlcpy(exit_code, "1", 2);
	exit_args = malloc(sizeof(char *) * 2);
	if (!exit_args)
		return ;
	exit_args[0] = exit_code;
	exit_args[1] = NULL;
	exit_cmd(exit_args, NULL);
	free(exit_args);
}

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
	cleanup_on_exit(environ);
	return (1);
}
