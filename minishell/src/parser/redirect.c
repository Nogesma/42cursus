/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:27:15 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:27:17 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/13/22.
//

#include <unistd.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

#include "../utils/error.h"
#include "../utils/global.h"
#include "parse_env.h"
#include "redirect.h"
#include "heredoc.h"
#include "../utils/parsing.h"
#include "rec_mult.h"
#include "../utils/pipes.h"

static int	word_size_redirect(char *s, t_list **env)
{
	int	i;
	int	is_special;
	int	size;

	i = 0;
	is_special = 0;
	size = 0;
	while (ft_isspace(s[i]))
		s++;
	while (s[i] && ((!ft_isspace(s[i]) && s[i] != '<' && s[i] != '>') || is_special))
	{
		if (s[i] == '\'' && is_special != 1)
			is_special = is_special ^ -1;
		else if (s[i] == '"' && is_special != -1)
			is_special = is_special ^ 1;
		else if (s[i] == '$' && is_special != -1)
			get_env_size(s, env, &size, &i);
		else
			size++;
		i++;
	}
	return (size);
}

static char	*next_word_redirect(char *line, t_list **env)
{
	int		pos;
	char	*new;
	int		is_special;
	int		i;

	pos = 0;
	new = (char *)ft_calloc((word_size_redirect(line, env) + 1), sizeof(char));
	if (!new)
		return (NULL);
	is_special = 0;
	i = 0;
	while (line[pos] && ft_isspace(line[pos]))
		pos++;
	while (line[pos] && ((!ft_isspace(line[pos])
			&& line[pos] != '<' && line[pos] != '>') || is_special))
	{
		if (line[pos] == '\'' && is_special != 1)
			is_special = is_special ^ -1;
		else if (line[pos] == '"' && is_special != -1)
			is_special = is_special ^ 1;
		else if (line[pos] == '$' && is_special != -1)
			pos += unpack_env(line + pos, new, env, &i);
		else
			new[i++] = line[pos];
		pos++;
	}
	new[i] = 0;
	return (new);
}

static int	find_next_redirect(char *line, t_list **env, char **target)
{
	int	ret;

	ret = -1;
	while (*line)
	{
		skip_till_valid(&line);
		if (ft_strncmp(line, ">>", 2) == 0)
			ret = 0;
		else if (ft_strncmp(line, ">", 1) == 0)
			ret = 1;
		else if (ft_strncmp(line, "<<", 2) == 0)
			ret = 2;
		else if (ft_strncmp(line, "<", 1) == 0)
			ret = 3;
		if (ret == 0 || ret == 2)
			line[1] = ' ';
		if (ret >= 0)
		{
			line[0] = ' ';
			if (ret == 0 || ret == 2)
				line++;
			line++;
			*target = next_word_redirect(line, env);
			line += erase_word(line);
			return (ret);
		}
		line++;
	}
	*target = NULL;
	return (-1);
}

static int	redirect_out(char *target, int token, t_pipe *fd)
{
	close_pipes(fd->out);
	fd->out[0] = 0;
	if (token == 0)
		fd->out[1] = open(target, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (token == 1)
		fd->out[1] = open(target, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd->out[1] == -1)
		return (minish_err(target));
	return (0);
}

static int	redirect_in(char *target, t_pipe *fd)
{
	close_pipes(fd->in);
	fd->in[1] = 0;
	fd->in[0] = open(target, O_RDONLY);
	if (fd->in[0] == -1)
		return (minish_err(target));
	return (0);
}

static int	heredoc_insert(char *target, t_pipe *fd)
{
	int		p[2];
	int		status;
	pid_t	pid;

	close_pipes(fd->in);
	fd->in[1] = 0;
	if (pipe(p))
		return (minish_err("pipe error"));
	pid = heredoc(target, p[1]);
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != 2)
		{
			status_code(1, WEXITSTATUS(status));
			fd->in[0] = p[0];
			if (fd->in[0] == -1)
				return (minish_err("pipe error"));
		}
		else
			return (status_code(1, 1));
	}
	close(p[1]);
	return (0);
}

int	set_redirects(char *line, t_list **env, t_pipe *fd)
{
	char	*target;
	int		token;

	token = find_next_redirect(line, env, &target);
	while (token >= 0)
	{
		if ((token == 0 || token == 1) && redirect_out(target, token, fd))
			return (1);
		if (token == 3 && redirect_in(target, fd))
			return (1);
		if (token == 2 && heredoc_insert(target, fd))
			return (1);
		if (target != NULL)
			free(target);
		token = find_next_redirect(line, env, &target);
	}
	if (target != NULL)
		free(target);
	return (0);
}
