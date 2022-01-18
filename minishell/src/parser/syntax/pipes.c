/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:22:32 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 02:22:34 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../../utils/parsing.h"
#include "../../utils/error.h"

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
				return (syntax_error("|"));
			has_char = 0;
		}
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (syntax_error("|"));
	return (0);
}
