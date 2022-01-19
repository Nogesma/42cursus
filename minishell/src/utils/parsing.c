/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:31:03 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:31:05 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/17/22.
//

#include <libft.h>

//skips all characters inhibited by " or ' in line
int	skip_till_valid(char **line)
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

//erases next word in line ending in space, <, > or \0
int	erase_word(char *line)
{
	char	*tmp;
	int		pos;

	pos = 0;
	while (line[pos] && ft_isspace(line[pos]))
		pos++;
	while (line[pos] && !ft_isspace(line[pos])
		&& line[pos] != '<' && line[pos] != '>')
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
