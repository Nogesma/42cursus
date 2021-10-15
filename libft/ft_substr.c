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
	dest = (char *)ft_calloc((len + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (dest);
	i = 0;
	while (s[start] && i < len)
		dest[i++] = s[start++];
	dest[i] = 0;
	return (dest);
}
