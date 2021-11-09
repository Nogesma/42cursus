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
	int	v;
	int	r;
	int	g;
	int	b;

	if (iterations == max_iterations)
		return (0);
	v = (int)((double)iterations / (double)max_iterations * 255);
	r = (int)(((double)c->er - (double)c->sr) * v / (255));
	g = (int)(((double)c->eg - (double)c->sg) * v / (255));
	b = (int)(((double)c->eb - (double)c->sb) * v / (255));
	if (c->er > c->sr)
		r += c->sr;
	else
		r += c->er;
	if (c->eg > c->sg)
		g += c->sg;
	else
		g += c->eg;
	if (c->eb > c->sb)
		b += c->sb;
	else
		b += c->eb;
	return (rgb_to_int(r, g, b));
}
