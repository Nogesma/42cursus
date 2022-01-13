//
// Created by Tadeusz Kondracki on 1/13/22.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "redirect.h"

static int	set_redirects(char *line, t_list **env, int *sfd, int *of) // todo malloc secure
{
	char	*target;
	int		token;

	token = find_next_redirect(&target);
	while (token >= 0)
	{
		if (token == 0 || token == 1)
			redirect_out(target, token);
		if (token == 2)
			redirect_in(target);
		if (token == 3)
			heredoc_shenanigans(target);
		free(target);
		token = find_next_redirect(&target);
	}
	free(target);
	return (0);
}

int	redirects(char *line, t_list **env, int set)
{
	static int	saved_fd[2] = {-1, -1};
	static int	open_files[2];

	if (set == 1)
		return (set_redirects(line, env, saved_fd, open_files));
	else
	{
		if (saved_fd[1] != -1 && !close(open_files[1])
			&& dup2(saved_fd[1], 1) == -1)
		{
			perror("minishell : pipe error :");
			return (1);
		}
		if (saved_fd[0] != -1 && !close(open_files[0])
			&& dup2(saved_fd[0], 0) == -1)
		{
			perror("minishell : pipe error :");
			return (1);
		}
	}
	return (0);
}
