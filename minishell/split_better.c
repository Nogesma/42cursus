//
// Created by tkondrac on 10.12.21.
//

#include "minishell.h"
#include "libft.h"

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
		if (!is_quote && !is_apostrophe && ' ' == str[i] && ' ' != str[i + 1])
			size++;
		i++;
	}
	if (' ' == str[0])
		return (size);
	return (size + 1);
}

static int	get_env_name_size(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

static int	word_size(char *s, t_list **env)
{
	int	i;
	int	is_special;
	int	size;

	i = 0;
	is_special = 0;
	size = 0;
	while (s[i] == ' ')
		s++;
	while (s[i] && (s[i] != ' ' || is_special))
	{
		if (s[i] == '\'' && is_special != 1)
			is_special = is_special ^ -1;
		else if (s[i] == '"' && is_special != -1)
			is_special = is_special ^ 1;
		else if (s[i] == '$' && is_special != -1)
		{
			size += (int)ft_strlen(get_env(env, s + i + 1));
			i += get_env_name_size(s + i);
		}
		else
			size++;
		i++;
	}
	return (size);
}

static int	unpack_env(char *s, char *new, t_list **env, int *i)
{
	char	*env_val;
	int		j;

	if (!s[1])
	{
		new[(*i)++] = '$';
		return (1);
	}
	env_val = get_env(env, s + 1);
	if (!env_val)
		return (get_env_name_size(s + 1));
	j = 0;
	while (env_val[j])
		new[(*i)++] = env_val[j++];
	return (get_env_name_size(s + 1));
}

static char	*next_word(char *s, t_list **env)
{
	static int	pos;
	char		*new;
	int			is_special;
	int			i;

	if (!s || !env)
	{
		pos = 0;
		return (NULL);
	}
	is_special = 0;
	i = 0;
	while (s[pos] == ' ')
		pos++;
	new = (char *)ft_calloc(sizeof(char), (word_size(s + pos, env) + 1));
	if (!new)
		return (NULL);
	while (s[pos] && (s[pos] != ' ' || is_special))
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
