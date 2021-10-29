/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:18:30 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:18:31 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	i = ft_strlen(&s[start]);
	if (len < i)
		i = len;
	dest = (char *)ft_calloc((i + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, &s[start], i + 1);
	return (dest);
}
