/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:20 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*get_env(t_list **env, char *name)
{
	t_list	*elem;
	size_t	len;
	char	*content;

	elem = *env;
	while (elem)
	{
		len = 0;
		content = elem->content;
		while (content[len] && content[len] != '='
			&& ft_isalnum(name[len]) && content[len] == name[len])
			len++;
		if (content[len] == '=' && !ft_isalnum(name[len]))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

char	*get_env_content(t_list **env, char *name)
{
	t_list	*elem;
	char	*content;

	elem = get_env(env, name);
	if (!elem)
		return (NULL);
	content = elem->content;
	while (*content != '=')
		content++;
	content++;
	return (content);
}
