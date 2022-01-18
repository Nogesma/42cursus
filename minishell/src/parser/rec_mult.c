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
#include <stdbool.h>

#include "../exec/exec.h"
#include "rec_mult.h"
#include "../utils/global.h"
#include "../utils/error.h"
#include "../utils/parsing.h"
#include "redirect.h"

static int	pipe_in(int *saved_fd, int p[2]);
static int	pipe_out(int *saved_fd, int p[2]);

static int	is_parenthesis(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (-1);
	return (0);
}

//finds next occurence of tokens &&, || or | in string, zeros their chars,
// stores pointer to characters just
// after in cmd_two and returns which one it found, -1 if none
static int	find_token(char *line, char **cmd_two)
{
	int	p_count;

	p_count = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (!*line)
			break ;
		p_count += is_parenthesis(*line);
		if (!p_count && !ft_strncmp(line, "&&", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (0);
		}
		else if (!p_count && !ft_strncmp(line, "||", 2))
		{
			line[0] = 0;
			line[1] = 0;
			*cmd_two = line + 2;
			return (1);
		}
		else if (!p_count && !ft_strncmp(line, "|", 1))
		{
			line[0] = 0;
			*cmd_two = line + 1;
			return (2);
		}
		line++;
	}
	return (-1);
}

static int	pipe_manage(int set, t_pipe_data *data)
{
	if (set == 1)
		return (pipe_in(&(data->saved_fd_pipe[0]), data->p));
	if (set == 0)
		return (pipe_out(&(data->saved_fd_pipe[1]), data->p));
	if (data->saved_fd_pipe[0] != -1 && dup2(data->saved_fd_pipe[0], 1) == -1)
		return (minish_err("pipe error"));
	close(data->saved_fd_pipe[0]);
	data->saved_fd_pipe[0] = -1;
	if (data->saved_fd_pipe[1] != -1 && dup2(data->saved_fd_pipe[1], 0) == -1)
		return (minish_err("pipe error"));
	close(data->saved_fd_pipe[1]);
	data->saved_fd_pipe[0] = -1;
	return (0);
}

static int	pipe_in(int *saved_fd, int p[2])
{
	*saved_fd = dup(1);
	if (*saved_fd == -1)
		return (minish_err("pipe error"));
	if (pipe(p) == -1)
		return (minish_err("pipe error"));
	if (dup2(p[1], 1) == -1)
		return (minish_err("pipe error"));
	close(p[1]);
	return (0);
}

static int	pipe_out(int *saved_fd2, int p[2])
{
	*saved_fd2 = dup(0);
	if (*saved_fd2 == -1)
		return (minish_err("pipe error"));
	if (dup2(p[0], 0) == -1)
		return (minish_err("pipe error"));
	close(p[0]);
	return (0);
}

int	check_parenthesis(char **line)
{
	char	*pos;
	int		count;

	pos = *line;
	while (ft_isspace(*pos))
		pos++;
	if (*pos != '(')
		return (0);
	count = 1;
	pos++;
	*line = pos;
	while (count > 0 && *pos)
	{
		pos++;
		skip_till_valid(&pos);
		if (!*pos)
			break ;
		if (*pos == '(')
			count++;
		else if (*pos == ')')
			count--;
	}
	*pos = 0;
	return (1);
}

int	cmds_redirect(char *line, t_list **env, int has_pipes)
{
	int	ret;

	if (check_parenthesis(&line))
		return (cmds_loop(line, env));
	if (redirects(line, env, 1))
	{
		status_code(1, 1);
		return (0);
	}
	ret = search_exec(line, env, has_pipes);
	redirects(line, env, 0);
	return (ret);
}

void	wait_forks(int *forks)
{
	int	status;

	status = -1;
	while ((*forks)-- > 0)
		wait(&status);
	*forks = 0;
	is_fork(1, 0);
	if (status != -1 && status_code(0, 0) != 130 && WIFEXITED(status))
		status_code(1, WEXITSTATUS(status));
}

void	do_cmds(char *line, t_list **env, t_pipe_data *data, int *forks)
{
	if (data->token == 2)
	{
		if (pipe_manage(1, data))
			return ;
		*forks += cmds_redirect(line, env, 1);
		if (pipe_manage(-1, data))
			return ;
		pipe_manage(0, data);
		return ;
	}
	if (data->token == 0)
	{
		*forks += cmds_redirect(line, env, *forks);
		wait_forks(forks);
	}
	if (data->token == 1)
	{
		*forks += cmds_redirect(line, env, *forks);
		wait_forks(forks);
	}
	pipe_manage(-1, data);
}

static void	init_pipe_data(t_pipe_data *dat)
{
	dat->token = -1;
	dat->p[1] = -1;
	dat->p[1] = -1;
	dat->saved_fd_pipe[1] = -1;
	dat->saved_fd_pipe[0] = -1;
}

int	cmds_loop(char *line, t_list **env)
{
	char		*cmd_two;
	t_pipe_data	data;
	int			forks;

	forks = 0;
	init_pipe_data(&data);
	data.token = find_token(line, &cmd_two);
	while (data.token >= 0)
	{
		do_cmds(line, env, &data, &forks);
		if ((status_code(0, 0) && data.token == 0)
			|| (!status_code(0, 0) && data.token == 1))
			return (forks);
		line = cmd_two;
		data.token = find_token(line, &cmd_two);
	}
	forks += cmds_redirect(line, env, forks);
	pipe_manage(-1, &data);
	return (forks);
}
