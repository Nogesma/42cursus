/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:15:36 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:15:37 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*s;

	if (!dst && !src)
		return (NULL);
	i = -1;
	dest = (char *)dst;
	s = (char *)src;
	while (++i < n)
		dest[i] = s[i];
	return (dst);
}
