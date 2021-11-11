/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:32:28 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/10 15:32:29 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterate.h"

int	pick_color(int iterations, t_colour *c)
{
	return ((iterations << c->a) + (iterations << c->b) + iterations * c->c);
}

int	iterate_mandelbrot(int maxiter, double x0, double y0, t_all *a)
{
	double	x;
	double	y;
	double	x2;
	double	y2;
	int		iterations;

	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	iterations = maxiter;
	while (iterations > 0 && (x2 + y2 <= 4))
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
		iterations--;
	}
	return (pick_color(iterations, a->colour));
}

int	iterate_julia(int maxiter, double zx, double zy, t_all *a)
{
	int		iterations;
	double	xtemp;

	iterations = maxiter;
	while (iterations > 0 && zx * zx + zy * zy < 4)
	{
		xtemp = zx * zx - zy * zy;
		zy = (zx + zx) * zy + a->fractal->cy;
		zx = xtemp + a->fractal->cx;
		iterations--;
	}
	return (pick_color(iterations, a->colour));
}
