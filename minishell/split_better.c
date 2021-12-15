//
// Created by tkondrac on 10.12.21.
//

#include "minishell.h"
#include "libft.h"

static int	ft_count(char *str)
{
    int	i;
    int	size;
    int is_apostrophe;
    int is_quote;

    i = 0;
    size = 0;
    is_apostrophe = 0;
    is_quote = 0;
    while (str[i + 1])
    {
        if (!is_quote && str[i] == 39)
            is_apostrophe= is_apostrophe^1;
        if (!is_apostrophe && str[i] == 34)
            is_quote= is_quote^1;
        if (!is_quote && !is_apostrophe && ' ' == str[i] && ' ' != str[i + 1])
            size++;
        i++;
    }
    if (' ' == str[0])
        return (size);
    return (size + 1);
}

static int  env_len(char *s, t_list **env, int *i){
    t_list  *pos;
    int     j;

    if (!s[1] || !ft_isalnum(s[1]))
        return (1);
    pos = *env;
    s++;
    while(pos)
    {
        j = 0;
        while (((char *)(pos->content))[j] && ((char *)(pos->content))[j] != '=' && ft_isalnum(s[j]))
        {
            if (((char *)(pos->content))[j] != s[j])
                break ;
            (*i)++;
            j++;
        }
        if (((char *)(pos->content))[j] == '=' && !ft_isalnum(s[j]))
            return (int)(ft_strlen(((char *)(pos->content)) + j + 1));
        pos = pos->next;
    }
    return (0);
}

static int  word_size(char *s, t_list **env)
{
    int i;
    int is_special;
    int size;

    i = 0;
    is_special = 0;
    size = 0;
    while (s[i] && (s[i] != ' ' || is_special))
    {
        if(s[i] == 39 && is_special != 1)
            is_special = is_special^-1;
        else if(s[i] == 34 && is_special != -1)
            is_special = is_special^1;
        else if(s[i] == '$' && is_special != -1)
            size += env_len(s + i, env, &i);
        else
            size++;
        i++;
    }
    return (size);
}

static int  unpack_env(char *s, char *new, t_list **env, int *i)
{
    char    *env_val;
    int     size;
    int     j;

    if (!s[1] || !ft_isalnum(s[1]))
    {
        new[(*i)++] = '$';
        return (1);
    }
    env_val = get_env_value(s + 1, env, &size);
    if (!env_val)
        return (0);
    j = 0;
    while(env_val[j])
        new[(*i)++] = env_val[j++];
    return (j);
}

static char *next_word(char *s, t_list **env)
{
    static int  pos;
    char        *new;
    int         is_special;
    int         i;

    if (!s || !env)
    {
        pos = 0;
        return (NULL);
    }
    is_special = 0;
    i = 0;
    new = malloc(sizeof(char) * (word_size(s + pos, env) + 1));
    if (!new)
        return (NULL);
    while(s[pos] && (s[pos] != ' ' || is_special))
    {
        if(s[pos] == 39 && is_special != 1)
            is_special = is_special^-1;
        else if(s[pos] == 34 && is_special != -1)
            is_special = is_special^1;
        else if(s[pos] == '$' && is_special != -1)
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
    int     i;

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
    print_args_debug(dest);
    return (dest);
}
