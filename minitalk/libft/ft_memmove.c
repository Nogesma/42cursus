/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:15:42 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:15:44 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*s;

	if (!dst && !src)
		return (NULL);
	dest = (char *)dst;
	s = (char *)src;
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dest[i] = s[i];
		}
		return (dst);
	}
	i = -1;
	while (++i < len)
		dest[i] = s[i];
	return (dst);
}
