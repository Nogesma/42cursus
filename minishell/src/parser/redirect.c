//
// Created by Tadeusz Kondracki on 1/13/22.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse_env.h"
#include "redirect.h"

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

static char *next_word_redirect(char *line, t_list **env)
{
	int			pos;
	char		*new;
	int			is_special;
	int			i;

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

static int	skip_till_valid(char **line)
{
	if (**line == '"')
	{
		(*line)++;
		while (**line != '"' && **line)
			(*line)++;
		if (**line)
			(*line)++;
	}
	else if (**line == '\'')
	{
		(*line)++;
		while (**line != '\'' && **line)
			(*line)++;
		if (**line)
			(*line)++;
	}
	else
		return (0);
	return (1);
}

static int	erase_word(char *line)
{
	char	*tmp;
	int		pos;

	pos = 0;
	while(line[pos] && line[pos] == ' ')
		pos++;
	while(line[pos] && line[pos] != ' ' && line[pos] != '<' && line[pos] != '>')
	{
		tmp = line + pos;
		if (skip_till_valid(&tmp))
		{
			while (line + pos != tmp)
				line[pos++] = ' ';
		}
		else
			line[pos++] = ' ';
	}
	return (pos);
}

static int	find_next_redirect(char *line, t_list **env, char **target)
{
	int	ret;

	ret = -1;
	while(*line)
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

static int	set_redirects(char *line, t_list **env, int *sfd, int *of) // todo malloc secure
{
	char	*target;
	int		token;

	(void)sfd;
	(void)of;
	token = find_next_redirect(line, env, &target);
	while (token >= 0)
	{
		if (token == 0 || token == 1)
			printf("target:%s| line:%s|\n", target, line);
//			redirect_out(target, token);
		if (token == 2)
			printf("target:%s| line:%s|\n", target, line);
//			redirect_in(target);
		if (token == 3)
			printf("target:%s| line:%s|\n", target, line);
//			heredoc_shenanigans(target);
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
