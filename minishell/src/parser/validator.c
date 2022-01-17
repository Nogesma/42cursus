/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:29:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:29:37 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../utils/parsing.h"

int	print_error(char *err)
{
	ft_printf(2, "minish: syntax error near unexpected token `%s`\n", err);
	return (1);
}

int	check_quotes(char *line)
{
	char	single_quote;
	char	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			++single_quote;
		if (*line == '"')
			++double_quote;
		++line;
	}
	if (single_quote % 2)
		return (print_error("'"));
	if (double_quote % 2)
		return (print_error("\""));
	return (0);
}

int	check_pipes(char *line)
{
	char	*line_head;
	char	has_char;

	line_head = line;
	has_char = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (*line == '|')
		{
			if (line > line_head && *(line - 1) == '|')
				has_char = 1;
			if (!has_char)
				return (print_error("|"));
			has_char = 0;
		}
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (print_error("|"));
	return (0);
}

int	check_double(char *line, char *token)
{
	char	*line_head;
	char	has_char;

	line_head = line;
	has_char = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (!ft_strncmp(token, line, 2))
		{
			if (!has_char)
				return (print_error(token));
			has_char = 0;
		}
		else if (line > line_head && !ft_strncmp(token, line - 1, 2))
			has_char = 0;
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (print_error(token));
	return (0);
}

int	check_redir(char *line, char *token)
{
	char	*line_head;
	char	has_char;

	line_head = line;
	has_char = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (!ft_strncmp(token, line, 2)
			|| (line > line_head && !ft_strncmp(token, line - 1, 2)))
			has_char = 0;
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (print_error("newline"));
	return (0);
}

int	check_line(char *line)
{
	return (check_quotes(line) || check_double(line, "&&")
		|| check_double(line, "||") || check_pipes(line)
		|| check_redir(line, ">>") || check_redir(line, "<<")
		|| check_redir(line, "<") || check_redir(line, ">"));
}
