/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:10:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/13 16:10:34 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <libft.h>

static char	*strjoin_nl(char *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	str = (char *)ft_calloc(s1l + s2l + 2, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1l + 1);
	str[s1l] = '\n';
	ft_strlcpy(str + s1l + 1, s2, s2l + 1);
	free(s1);
	return (str);
}

char	*heredoc(char *word)
{
	char	*line;
	char	*buffer;
	size_t	wordsize;

	wordsize = ft_strlen(word) + 1;
	buffer = (char *)ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(word, line, wordsize))
		{
			buffer = ft_strjoin(buffer, "\n");
			if (!buffer)
				return (NULL);
			return (buffer);
		}
		buffer = strjoin_nl(buffer, line);
		if (!buffer)
			return (NULL);
		free(line);
		line = readline("> ");
	}
	return (buffer);
}
