/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:22:21 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 02:22:25 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../../utils/parsing.h"
#include "../../utils/error.h"

int	closed_brace(char **line, int *braces, int has_char)
{
	if (!has_char)
		return (syntax_error(")"));
	++(*line);
	while (ft_isspace(**line))
		++(*line);
	if (**line == ')' || **line == '(')
		--(*line);
	else if (**line && ft_strncmp(*line, "&&", 2) && ft_strncmp(*line, "||", 2)
		&& ft_strncmp(*line, "|", 1))
		return (syntax_error(")"));
	--(*braces);
	return (0);
}

int	check_char(char **line, int *braces, char *has_char, char *has_token)
{
	if (**line == ')')
		return (closed_brace(line, braces, *has_char));
	else if (**line == '(')
	{
		if (!*has_token)
			return (syntax_error("("));
		++(*braces);
		*has_char = 0;
	}
	else if (!ft_isspace(**line))
	{
		*has_char = 1;
		*has_token = 0;
	}
	return (0);
}

int	is_token(char *line, const char *line_head)
{
	return (!ft_strncmp(line, "|", 1)
		|| (line > line_head && (!ft_strncmp(line - 1, "&&", 2)
				|| !ft_strncmp(line - 1, "||", 2))));
}

int	check_braces(char *line, char	*line_head)
{
	int		braces;
	char	has_token;
	char	has_char;

	braces = 0;
	has_token = 1;
	has_char = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (braces < 0)
			return (syntax_error(")"));
		if (check_char(&line, &braces, &has_char, &has_token))
			return (1);
		if (is_token(line, line_head))
			has_token = 1;
		++line;
	}
	if (braces != 0)
		return (syntax_error("("));
	return (0);
}
