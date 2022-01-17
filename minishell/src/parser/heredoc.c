/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:10:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/13 16:10:34 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

#include "../utils/global.h"

int	heredoc(char *word, int fd)
{
	char	*line;
	size_t	wordsize;
	pid_t	child;

	child = fork();
	if (child == -1)
		return (0);
	if (child == 0)
	{
		signal(SIGINT, exit);
		wordsize = ft_strlen(word) + 1;
		line = readline("> ");
		while (line)
		{
			if (!ft_strncmp(word, line, wordsize))
				exit(0);
			ft_printf(fd, "%s\n", line);
			free(line);
			line = readline("> ");
		}
		exit(1);
	}
	is_fork(1, 1);
	return (1);
}
