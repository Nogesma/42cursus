/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:01:42 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/04 19:01:44 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	click_and_drag(int x, int y, t_all *a)
{
	if (a->mlx->is_pressed)
	{
		a->fractal->cx = (double)x / a->mlx->width * 2 - 1;
		a->fractal->cy = (double)y / a->mlx->height * 2 - 1;
		update_image(a);
	}
	return (1);
}

int	release(int button, int x, int y, t_all *all)
{
	if (button == 1)
		all->mlx->is_pressed = 0;
	return (1);
}

int	mouse_event(int button, int x, int y, t_all *a)
{
	double	xm;
	double	ym;

	xm = a->fractal->dx * x + a->fractal->x_min;
	ym = a->fractal->dy * y + a->fractal->y_min;
	if (button == 4)
		a->fractal->dx /= a->fractal->zoom;
	if (button == 4)
		a->fractal->dy /= a->fractal->zoom;
	if (button == 5)
		a->fractal->dx *= a->fractal->zoom;
	if (button == 5)
		a->fractal->dy *= a->fractal->zoom;
	if (button == 1)
	{
		a->mlx->is_pressed = 1;
		return (click_and_drag(x, y, a));
	}
	a->fractal->x_min = xm - x * a->fractal->dx;
	a->fractal->x_max = xm + (a->mlx->width - x) * a->fractal->dx;
	a->fractal->y_min = ym - y * a->fractal->dy;
	a->fractal->y_max = ym + (a->mlx->height - y) * a->fractal->dy;
	update_image(a);
	return (1);
}

int	kbd_event(int button, t_all *a)
{
	double	stepx;
	double	stepy;

	stepx = a->fractal->dx * 8;
	stepy = a->fractal->dy * 8;
	if (button == 124)
		apply_step(&(a->fractal->x_min), &(a->fractal->x_max), stepx, add);
	else if (button == 123)
		apply_step(&(a->fractal->x_min), &(a->fractal->x_max), stepx, subtract);
	else if (button == 125)
		apply_step(&(a->fractal->y_min), &(a->fractal->y_max), stepy, add);
	else if (button == 126)
		apply_step(&(a->fractal->y_min), &(a->fractal->y_max), stepy, subtract);
	else if (button == 15)
		julia(a);
	else if (button == 53)
	{
		mlx_destroy_image(a->mlx->mlx_ptr, a->mlx->image);
		exit(0);
	}
	update_image(a);
	return (1);
}
