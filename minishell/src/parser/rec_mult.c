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

int	cmds_redirect(char *line, t_list **env, t_pipe *fd)
{
	int	ret;

	if (check_parenthesis(&line))
		return (cmds_loop(line, env, fd));
	if (redirects(line, env, 1))
	{
		status_code(1, 1);
		return (0);
	}
	ret = search_exec(line, env, fd);
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

void	close_pipes(int fd[2])
{
	if (fd[0] != fd[1])
	{
		close(fd[0]);
		close(fd[1]);
	}
}

int	do_cmds(char *line, t_list **env, t_pipe *fd, int *forks, t_pipe *data)
{
	fd->out[0] = data->out[0];
	fd->out[1] = data->out[1];
	if (fd->token == 2)
	{
		if (pipe(fd->out) == -1)
			return (minish_err("pipe error"));
		*forks += cmds_redirect(line, env, fd);
		close_pipes(fd->in);
		fd->in[0] = fd->out[0];
		fd->in[1] = fd->out[1];
	}
	else
	{
		*forks += cmds_redirect(line, env, fd);
		wait_forks(forks);
		close_pipes(fd->in);
		fd->in[0] =  data->in[0];
		fd->in[1] =  data->in[1];
	}
	return (0);
}

static void	init_pipe_data(t_pipe *fd, t_pipe *data)
{
	fd->token = -1;
	fd->out[0] = data->out[0];
	fd->out[1] = data->out[1];
	fd->in[0] =  data->in[0];
	fd->in[1] =  data->in[1];
}

int	cmds_loop(char *line, t_list **env, t_pipe *data)
{
	char	*cmd_two;
	t_pipe	fd;
	int		forks;

	forks = 0;
	init_pipe_data(&fd, data);
	fd.token = find_token(line, &cmd_two);
	while (fd.token >= 0)
	{
		do_cmds(line, env, &fd, &forks, data);
		if ((status_code(0, 0) && fd.token == 0)
			|| (!status_code(0, 0) && fd.token == 1))
			return (forks);
		line = cmd_two;
		fd.token = find_token(line, &cmd_two);
	}
	fd.out[0] = data->out[0];
	fd.out[1] = data->out[1];
	forks += cmds_redirect(line, env, &fd);
	close_pipes(fd.in);
	return (forks);
}
