/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:49 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/20 14:32:51 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 19.01.22.
//

#include <libft.h>

#include "redirect_parse.h"
#include "parse_env.h"

static int	word_size_redirect(char *s, t_list **env)
{
	int	i;
	int	is_special;
	int	size;

	i = 0;
	is_special = 0;
	size = 0;
	while (ft_isspace(s[i]))
		s++;
	while (s[i] && ((!ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
			|| is_special))
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

static void	init_zero(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static char	*init_word(char *line, t_list **env, char **new)
{
	*new = (char *)ft_calloc((word_size_redirect(line, env) + 1), sizeof(char));
	return (*new);
}

char	*next_word_redirect(char *line, t_list **env)
{
	int		pos;
	char	*new;
	int		is_special;
	int		i;

	if (!init_word(line, env, &new))
		return (NULL);
	init_zero(&pos, &is_special, &i);
	while (line[pos] && ft_isspace(line[pos]))
		pos++;
	while (line[pos] && ((!ft_isspace(line[pos])
				&& line[pos] != '<' && line[pos] != '>') || is_special))
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

int	which_redirect(char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		return (0);
	else if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(line, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(line, "<", 1) == 0)
		return (3);
	return (-1);
}
