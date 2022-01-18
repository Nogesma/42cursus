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

int	open_brace(char **line, int *braces, int has_char)
{
	if (**line == ')')
	{
		if (!has_char)
			return (syntax_error("a)"));
		++(*line);
		while (ft_isspace(**line))
			++(*line);
		if (**line == ')' || **line == '(')
			--(*line);
		else if (**line && ft_strncmp(*line, "&&", 2) && ft_strncmp(*line, "||", 2)
				 && ft_strncmp(*line, "|", 1))
			return (syntax_error("b)"));
		--(*braces);
	}
	return (0);
}

int	check_braces(char *line)
{
	char	*line_head;
	int		braces;
	char	has_token;
	char	has_char;

	line_head = line;
	braces = 0;
	has_token = 1;
	has_char = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (braces < 0)
			return (syntax_error("c)"));
		if (*line == ')' && open_brace(&line, &braces, has_char))
			return (1);
		else if (*line == '(')
		{
			if (!has_token)
				return (syntax_error("("));
			++braces;
			has_char = 0;
		}
		else if (!ft_isspace(*line))
		{
			has_char = 1;
			has_token = 0;
		}
		if (!ft_strncmp(line, "|", 1) || (line > line_head
			&& (!ft_strncmp(line - 1, "&&", 2) || !ft_strncmp(line - 1, "||", 2))))
			has_token = 1;
		++line;
	}
	if (braces != 0)
		return (syntax_error("("));
	return (0);
}
