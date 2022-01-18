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
				return (syntax_error(token));
			has_char = 0;
		}
		else if (line > line_head && !ft_strncmp(token, line - 1, 2))
			has_char = 0;
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (!has_char)
		return (syntax_error(token));
	return (0);
}
