/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:33:43 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 23:33:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 26.12.21.
//

#include <libft.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "../exec/exec.h"
#include "rec_mult.h"
#include "../utils/global.h"

static int pipe_in(int *saved_fd, int p[2]);
static int pipe_out(int *saved_fd, int p[2]);

//finds next occurence of tokens &&, || or | in string, zeros their chars,
// stores pointer to characters just
// after in cmd_two and returns which one it found, -1 if none
static int	find_token(char *line, char **cmd_two)
{
	while (*line)
	{
		if (!ft_strncmp(line, "&&", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (0);
		}
		else if (!ft_strncmp(line, "||", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (1);
		}
		else if (!ft_strncmp(line, "|", 1))
		{
			line[0] = 0;
			*cmd_two = line + 1;
			return (2);
		}
		line++;
	}
	return (-1);
}

int static	pipe_manage(int set)
{
	static int	saved_fd = -1;
	static int	saved_fd2 = -1;
	static int	p[2];

	if (set == 1)
	{
		return pipe_in(&saved_fd, p);
	}
	if (set == 0)
		return pipe_out(&saved_fd2, p);
	if (saved_fd != -1 && dup2(saved_fd, 1) == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	close(saved_fd);
	saved_fd = -1;
	if (saved_fd2 != -1 && dup2(saved_fd2, 0) == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	close(saved_fd2);
	saved_fd2 = -1;
	return (0);
}

static int pipe_in(int *saved_fd, int p[2])
{
	*saved_fd = dup(1);
	if (*saved_fd == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	if (pipe(p) == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	if (dup2(p[1], 1) == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	close(p[1]);
	return (0);
}

static int pipe_out(int *saved_fd2, int p[2])
{
	*saved_fd2 = dup(0);
	if (*saved_fd2 == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	if (dup2(p[0], 0) == -1)
	{
		perror("minishell : pipe error :");
		return (1);
	}
	close(p[0]);
	return (0);
}

int	cmds_redirect(char *line, t_list **env, char has_pipes)
{
	int	forks;
//	set_redirect(line, env);
	forks = search_exec(line, env, has_pipes);
//	unset_redirect(line, env);
	return (forks);
}

void	wait_forks(int *forks)
{
	int	status;

	status = -1;
	while ((*forks)-- > 0)
		wait(&status);
	is_fork(1, 0);
	if (status != -1 && status_code(0, 0) != 130 && WIFEXITED(status))
		status_code(1, WEXITSTATUS(status));
}

int	do_cmds(char *line, t_list **env, int token)
{
	static int	forks;

	if (token == 2)
	{
		if (pipe_manage(1))
			return (0);
		forks += cmds_redirect(line, env, 1);
		if (pipe_manage(-1))
			return (forks);
		pipe_manage(0);
		return (forks);
	}
	if (token == 0)
	{
		forks += cmds_redirect(line, env, forks);
		wait_forks(&forks);
	}
	if (token == 1)
	{
		forks += cmds_redirect(line, env, forks);
		wait_forks(&forks);
	}
	pipe_manage(-1);
	return (0);
}

void	cmds_loop(char *line, t_list **env)
{
	char	*cmd_two;
	int		token;
	int		forks;

	forks = 0;
	token = find_token(line, &cmd_two);
	while (token >= 0)
	{
		forks += do_cmds(line, env, token);
		if ((status_code(0, 0) && token == 0) || (!status_code(0, 0) && token == 1))
			return ;
		line = cmd_two;
		token = find_token(line, &cmd_two);
	}
	forks += cmds_redirect(line, env, 0);
	wait_forks(&forks);
	pipe_manage(-1);
}
