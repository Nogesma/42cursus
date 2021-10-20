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

	if (!dst && !src)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (&src[i] == &dst[0])
		{
			i = len;
			while (--i > 0)
				*(unsigned char *)&dst[i] = *(unsigned char *)&src[i];
			*(unsigned char *)&dst[i] = *(unsigned char *)&src[i];
			return (dst);
		}
	}
	i = -1;
	while (++i < len)
		*(unsigned char *) &dst[i] = *(unsigned char *) &src[i];
	return (dst);
}
