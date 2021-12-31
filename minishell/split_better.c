//
// Created by tkondrac on 10.12.21.
//

#include "minishell.h"

static int	count_wildcard(int is_wildcard)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;

	if (!is_wildcard)
		return (1);
	dir = opendir(".");
	if (!dir)
		return (0);
	dp = readdir(dir);
	i = 0;
	while (dp)
	{
		if (dp->d_name[0] != '.')
			i++;
		dp = readdir(dir);
	}
	closedir(dir);
	return (i);
}

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
			size += count_wildcard(str[i + 1] == '*'
					&& (str[i + 2] == ' ' || str[i + 2] == 0));
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
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

void	get_env_size(char *s, t_list **env, int *size, int *i)
{
	unsigned char	status;

	if (s[*i + 1] == '?')
	{
		status = status_code(0, 0);
		(*i)++;
		if (status < 10)
			(*size)++;
		else if (status < 100)
			(*size) += 2;
		else
			(*size) += 3;
		while (s[*i] && s[*i] != ' ')
			(*i)++;
	}
	else
	{
		*size += (int)ft_strlen(get_env_content(env, s + *i + 1));
		*i += get_env_name_size(s + *i + 1);
	}
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
			get_env_size(s, env, &size, &i);
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
	char	*status;

	if (s[1] == '?')
	{
		status = ft_itoa(status_code(0, 0));
		*i += (int)ft_strlcpy(new, status, 4);
		free(status);
		return (1);
	}
	if ((!s[1] || !ft_isalnum(s[1])))
	{
		new[(*i)++] = '$';
		return (1);
	}
	env_val = get_env_content(env, s + 1);
	if (!env_val)
		return (get_env_name_size(s + 1));
	j = 0;
	while (env_val[j])
		new[(*i)++] = env_val[j++];
	return (get_env_name_size(s + 1));
}

static void	get_dir_content(t_list **lst)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;
	t_list			*elem;

	dir = opendir(".");
	if (!dir)
		return ;
	dp = readdir(dir);
	i = 0;
	while (dp)
	{
		if (dp->d_name[0] != '.')
		{
			elem = new_lst(lst, elem, ft_strdup(dp->d_name));
			i++;
		}
		dp = readdir(dir);
	}
	closedir(dir);
	bubble_sort_lst(lst, i);
}

static char	*wildcard(int *pos)
{
	static t_list	**lst;
	t_list			*elem;
	char			*content;

	if (!lst)
	{
		lst = (t_list **)malloc(sizeof(t_list *));
		*lst = NULL;
		get_dir_content(lst);
	}
	elem = *lst;
	*lst = elem->next;
	content = elem->content;
	free(elem);
	if (!*lst)
	{
		free(lst);
		lst = NULL;
		(*pos)++;
	}
	return (content);
}

static int	special_word(char *s, t_list **env, int *pos, char **new)
{
	*new = NULL;
	if (!s || !env)
	{
		*pos = 0;
		return (1);
	}
	while (s[*pos] == ' ')
		(*pos)++;
	if (s[*pos] == '*' && (s[(*pos) + 1] == ' ' || s[(*pos) + 1] == 0))
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
