/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:17:00 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:17:02 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Static
static int	ft_strcpy(char *dest, const char *src)
{
	int			i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = 0;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	str = (char *)ft_calloc(s1l + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + s1l, s2);
	return (str);
}
