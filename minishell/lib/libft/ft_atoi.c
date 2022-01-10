/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:13:41 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/14 12:13:43 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	is_negative;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	is_negative = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		is_negative = -1;
		i++;
	}
	result = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - '0';
		++i;
	}
	return (result * is_negative);
}
