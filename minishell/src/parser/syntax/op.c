/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:22:27 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 02:22:29 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../../utils/parsing.h"
#include "../../utils/error.h"

static int	check_token(char *has_char, char *has_token, char *token)
{
	if (!(*has_char))
		return (syntax_error(token));
	*has_char = 0;
	*has_token = 1;
	return (0);
}

int	check_double(char *line, char *token)
{
	char	*line_head;
	char	has_char;
	char	has_token;

	line_head = line;
	has_char = 0;
	has_token = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (!ft_strncmp(token, line, 2)
			&& check_token(&has_char, &has_token, token))
			return (1);
		else if (line > line_head && !ft_strncmp(token, line - 1, 2))
			has_char = 0;
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (has_token && !has_char)
		return (syntax_error(token));
	return (0);
}
