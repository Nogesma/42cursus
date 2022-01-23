/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:38:26 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/12 15:38:35 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "../utils/global.h"
#include "../utils/environ.h"

//returns size of certain "$*" env variable, useful for advancing
//in line when parsing env variables
int	get_env_name_size(const char *s)
{
	int	i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

//returns strlen of env value
void	get_env_size(char *s, t_list **env, int *size, int *i)
{
	unsigned char	status;

	if (s[*i + 1] == '?')
	{
		status = status_code(0, 0);
		(*size)++;
		while (status / 10 != 0)
		{
			status = status / 10;
			(*size)++;
		}
		(*i)++;
	}
	else
	{
		*size += (int)ft_strlen(get_env_content(env, s + *i + 1));
		*i += get_env_name_size(s + *i + 1);
	}
}

int	unpack_env(char *s, char *new, t_list **env, int *i)
{
	char	*env_val;
	int		j;
	char	*status;

	if (s[1] == '?')
	{
		status = ft_itoa(status_code(0, 0));
		if (!status)
			return (1);
		*i += (int)ft_strlcpy(new + *i, status, ft_strlen(status) + 1);
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
