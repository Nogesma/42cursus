/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:16:47 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:16:49 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		size;
	char	*dest;

	size = ft_strlen(src) + 1;
	dest = (char *)ft_calloc(size, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, src, size);
	return (dest);
}
