/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:22:43 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 02:22:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../../utils/parsing.h"
#include "../../utils/error.h"

int	check_redir(char *line, char *token)
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
			|| (line > line_head && !ft_strncmp(token, line - 1, 2)))
		{
			has_token = 1;
			has_char = 0;
		}
		else if (!ft_isspace(*line))
			has_char = 1;
		++line;
	}
	if (has_token && !has_char)
		return (syntax_error("newline"));
	return (0);
}
