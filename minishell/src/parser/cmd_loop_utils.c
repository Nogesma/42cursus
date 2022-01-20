/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/20 14:32:38 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 19.01.22.
//

#include <libft.h>
#include "../utils/parsing.h"

#include "cmd_loop_utils.h"

//returns -1 for ) and 1 for ( otherwise 0
static int	is_parenthesis(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (-1);
	return (0);
}

//returns which token: &&, ||, | it is
static int	which_token(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (0);
	if (!ft_strncmp(line, "||", 2))
		return (1);
	if (!ft_strncmp(line, "|", 1))
		return (2);
	return (-1);
}

// finds next occurence of tokens &&, || or | in string, zeros their chars,
// stores pointer to characters just
// after in cmd_two and returns which one it found, -1 if none
int	find_token(char *line, char **cmd_two)
{
	int	p_count;
	int	token;

	p_count = 0;
	while (*line)
	{
		skip_till_valid(&line);
		if (!*line)
			break ;
		p_count += is_parenthesis(*line);
		token = which_token(line);
		if (!p_count && token != -1)
		{
			line[0] = 0;
			*cmd_two = line + 1;
			if (token == 2)
				return (token);
			line[1] = 0;
			*cmd_two = line + 2;
			return (token);
		}
		line++;
	}
	return (-1);
}

//checks if parenthesis present and if true, advances to char after first
//parenthesis. Zeros first and last parenthesis
int	check_parenthesis(char **line)
{
	char	*pos;
	int		count;

	pos = *line;
	while (ft_isspace(*pos))
		pos++;
	if (*pos != '(')
		return (0);
	count = 1;
	pos++;
	*line = pos;
	while (count > 0 && *pos)
	{
		pos++;
		skip_till_valid(&pos);
		if (!*pos)
			break ;
		count += is_parenthesis(*pos);
	}
	*pos = 0;
	return (1);
}
