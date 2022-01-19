/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:45:31 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:45:54 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "parse_env.h"
#include "wildcard.h"

static int	ft_count(const char *str)
{
	int	i;
	int	size;
	int	is_apostrophe;
	int	is_quote;

	i = 0;
	size = 0;
	is_apostrophe = 0;
	is_quote = 0;
	while (str[i + 1])
	{
		if (!is_quote && str[i] == '\'')
			is_apostrophe = is_apostrophe ^ 1;
		if (!is_apostrophe && str[i] == '"')
			is_quote = is_quote ^ 1;
		if (!is_quote && !is_apostrophe && ft_isspace(str[i])
			&& !ft_isspace(str[i + 1]))
			size += count_wildcard(str[i + 1] == '*'
					&& (ft_isspace(str[i + 2]) || str[i + 2] == 0));
		i++;
	}
	if (ft_isspace(str[0]))
		return (size);
	return (size + 1);
}

static int	word_size(char *s, t_list **env)
{
	int	i;
	int	is_special;
	int	size;

	i = 0;
	is_special = 0;
	size = 0;
	while (ft_isspace(s[i]))
		s++;
	while (s[i] && (!ft_isspace(s[i]) || is_special))
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

static int	special_word(char *s, t_list **env, int *pos, char **new)
{
	*new = NULL;
	if (!s || !env)
	{
		*pos = 0;
		return (1);
	}
	while (ft_isspace(s[*pos]))
		(*pos)++;
	if (s[*pos] == '*' && (ft_isspace(s[(*pos) + 1]) || s[(*pos) + 1] == 0))
	{
		*new = wildcard(pos);
		if (*new)
			return (1);
	}
	*new = (char *)ft_calloc((word_size(s + *pos, env) + 1), sizeof(char));
	if (!*new)
		return (1);
	return (0);
}

static char	*next_word(char *s, t_list **env)
{
	static int	pos;
	char		*new;
	int			is_special;
	int			i;

	if (special_word(s, env, &pos, &new))
		return (new);
	is_special = 0;
	i = 0;
	while (s[pos] && (!ft_isspace(s[pos]) || is_special))
	{
		if (s[pos] == '\'' && is_special != 1)
			is_special = is_special ^ -1;
		else if (s[pos] == '"' && is_special != -1)
			is_special = is_special ^ 1;
		else if (s[pos] == '$' && is_special != -1)
			pos += unpack_env(s + pos, new, env, &i);
		else
			new[i++] = s[pos];
		pos++;
	}
	new[i] = 0;
	return (new);
}

char	**ft_arg_split(char *s, t_list **env)
{
	char	**dest;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = 0;
	if (s[0])
		size = ft_count(s);
	dest = (char **)ft_calloc((size + 1), sizeof(char *));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		dest[i] = next_word(s, env);
		if (!dest[i])
			return (NULL);
	}
	dest[i] = next_word(NULL, NULL);
	return (dest);
}
