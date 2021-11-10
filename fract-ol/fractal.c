/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:41:54 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/10 15:41:55 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	mandelbrot(t_all *a)
{
	a->fractal->x_min = -2.0;
	a->fractal->x_max = 0.47;
	a->fractal->y_min = -1.12;
	a->fractal->y_max = 1.12;
	a->fractal->dx = (a->fractal->x_max - a->fractal->x_min) / a->mlx->width;
	a->fractal->dy = (a->fractal->y_max - a->fractal->y_min) / a->mlx->height;
	update_image(a);
	return (1);
}

int	julia(t_all *a)
{
	a->fractal->x_min = -2;
	a->fractal->x_max = 2;
	a->fractal->y_min = -2;
	a->fractal->y_max = 2;
	a->fractal->dx = (a->fractal->x_max - a->fractal->x_min) / a->mlx->width;
	a->fractal->dy = (a->fractal->y_max - a->fractal->y_min) / a->mlx->height;
	update_image(a);
	return (1);
}
