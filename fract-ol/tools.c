/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:26:55 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:26:59 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

unsigned int	rgb_to_int(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int	color;

	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	return (color);
}

unsigned int	pick_color(int max_iterations, int iterations, t_colour *c)
{
	if (iterations == max_iterations)
		return (0);
	return ((iterations << c->a) + (iterations << c->b) + iterations * c->c);
}

double	ft_atod(char *s)
{
	int	div;
	int	i;

	i = -1;
	while (s[++i] && s[i] != '.')
		;
	i--;
	div = 0;
	if (i != -1)
	{
		while (s[++i])
		{
			if (s[i + 1])
				s[i] = s[i + 1];
			div++;
		}
	}
	i = ft_atoi(s);
	return ((double) i / pow(10, div));
}
