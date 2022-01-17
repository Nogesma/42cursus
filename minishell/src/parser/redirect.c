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
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#include "../utils/error.h"
#include "../utils/global.h"
#include "parse_env.h"
#include "redirect.h"
#include "heredoc.h"
#include "../utils/parsing.h"

static int	word_size_redirecct(char *s, t_list **env)
{
	int	i;
	int	is_special;
	int	size;

	i = 0;
	is_special = 0;
	size = 0;
	while (s[i] == ' ')
		s++;
	while (s[i] && ((s[i] != ' ' && s[i] != '<' && s[i] != '>') || is_special))
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
	new = (char *)ft_calloc((word_size_redirecct(line, env) + 1), sizeof(char));
	if (!new)
		return (NULL);
	is_special = 0;
	i = 0;
	while (line[pos] && line[pos] == ' ')
		pos++;
	while (line[pos] && ((line[pos] != ' ' && line[pos] != '<' && line[pos] != '>') || is_special))
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

int	redirect_out(char *target, int token, int *sfd, int *of)
{
	if (sfd[1] == -1)
	{
		sfd[1] = dup(1);
		if (sfd[1] == -1)
			return (ft_perror("minishell: pipe error"));
	}
	else if (of[1] != -1)
		close(of[1]);
	if (token == 0)
	{
		of[1] = open(target, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (of[1] == -1 || dup2(of[1], 1) == -1)
			return (ft_perror("minishell: pipe error"));
	}
	if (token == 1)
	{
		of[1] = open(target, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (of[1] == -1 || dup2(of[1], 1) == -1)
			return (ft_perror("minishell: pipe error"));
	}
	return (0);
}

static int	redirect_in(char *target, int *sfd, int *of)
{
	if (sfd[0] == -1)
	{
		sfd[0] = dup(0);
		if (sfd[0] == -1)
			return (ft_perror("minishell: pipe error"));
	}
	else if (of[0] != -1)
		close(of[0]);
	of[0] = open(target, O_RDONLY);
	if (of[0] == -1 || dup2(of[0], 0) == -1)
		return (ft_perror("minishell: pipe error"));
	return (0);
}

static int	heredoc_insert(char *target, int *sfd, int *of)
{
	int	p[2];
	int	status;

	if (sfd[0] == -1)
	{
		sfd[0] = dup(0);
		if (sfd[0] == -1)
			return (ft_perror("minishell: pipe error"));
	}
	else if (of[0] != -1)
		close(of[0]);
	if (pipe(p))
		return (ft_perror("minishell: pipe error"));
	if (heredoc(target, p[1]))
	{
		wait(&status);
		if (WEXITSTATUS(status) != 2)
		{
			status_code(1, WEXITSTATUS(status));
			of[0] = p[0];
			if (of[0] == -1 || dup2(of[0], 0) == -1)
				return (ft_perror("minishell: pipe error"));
		}
		else
			return (status_code(1, 1));
	}
	close(p[1]);
	return (0);
}

static int	set_redirects(char *line, t_list **env, int *sfd, int *of) // todo malloc secure/return codes
{
	char	*target;
	int		token;

	(void)sfd;
	(void)of;
	token = find_next_redirect(line, env, &target);
	while (token >= 0)
	{
		if ((token == 0 || token == 1) && redirect_out(target, token, sfd, of))
			return (1);
		if (token == 3 && redirect_in(target, sfd, of))
			return (1);
		if (token == 2 && heredoc_insert(target, sfd, of))
			return (1);
		if (target != NULL)
			free(target);
		token = find_next_redirect(line, env, &target);
	}
	if (target != NULL)
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
			&& dup2(saved_fd[1], 1) == -1 && !close(saved_fd[1]))
			return (ft_perror("minishell: pipe error"));
		if (saved_fd[0] != -1 && !close(open_files[0])
			&& dup2(saved_fd[0], 0) == -1 && !close(saved_fd[0]))
			return (ft_perror("minishell: pipe error"));
		open_files[0] = -1;
		open_files[1] = -1;
		saved_fd[0] = -1;
		saved_fd[1] = -1;
	}
	return (0);
}
