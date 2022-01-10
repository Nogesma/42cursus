/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:15:16 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:15:17 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	get_last_digit(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return ('8');
		return (-n % 10 + '0');
	}
	return (n % 10 + '0');
}

char	*ft_itoa(int n)
{
	char	*inv_result;
	char	*result;
	int		i;
	int		j;

	inv_result = (char *)ft_calloc(13, sizeof(char));
	result = (char *)ft_calloc(13, sizeof(char));
	if (inv_result == NULL || result == NULL)
		return (NULL);
	i = 0;
	while (n / 10)
	{
		inv_result[i++] = get_last_digit(n);
		n /= 10;
	}
	inv_result[i] = get_last_digit(n);
	if (n < 0)
		inv_result[++i] = '-';
	j = 0;
	while (i >= 0)
		result[j++] = inv_result[i--];
	free(inv_result);
	inv_result = ft_strdup(result);
	free(result);
	return (inv_result);
}
