/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:17:08 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:17:09 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	int				r;

	i = 0;
	if (ft_strlen(dst) >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (dst[i])
		++i;
	r = i;
	j = 0;
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	if (dstsize != 0 && i <= dstsize)
		dst[i] = 0;
	while (src[j])
		j++;
	return (r + j);
}
