/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:16:24 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/12 09:16:25 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*strdup_m(unsigned int n, const char *src)
{
	unsigned int	i;
	char			terminated;
	char			*dest;

	dest = (char *)malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (0);
	i = 0;
	while (i <= n)
		dest[i++] = 0;
	terminated = 0;
	i = 0;
	while (i < n)
	{
		if (src[i] == '\0')
			terminated = 1;
		if (terminated)
			dest[i] = '\0';
		else
			dest[i] = src[i];
		++i;
	}
	return (dest);
}

static int	ft_count(const char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i + 1])
	{
		if (c == str[i] && c != str[i + 1])
			size++;
		i++;
	}
	if (c == str[0])
		return (size);
	return (size + 1);
}

static char	**new_str(char **dest, const char *str, char c)
{
	int	i;
	int	j;
	int	from;

	if (str[0] == 0)
		return (dest);
	i = 0;
	while (c == str[i++])
		;
	from = i - 1;
	j = 0;
	while (str[i - 1])
	{
		if (!str[i] && c != str[i - 1])
			dest[j++] = strdup_m(i - from, str + from);
		else if (c == str[i])
		{
			if (c != str[i - 1])
				dest[j++] = strdup_m(i - from, str + from);
			from = i + 1;
		}
		i++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		size;

	if (!s)
		return (NULL);
	size = 0;
	if (s[0])
		size = ft_count(s, c);
	dest = (char **)ft_calloc((size + 1), sizeof(char *));
	if (dest == NULL)
		return (NULL);
	dest = new_str(dest, s, c);
	return (dest);
}
