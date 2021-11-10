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

#include "main.h"

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
		a->fractal->cx = (double)x / a->mlx->width * 2 - 1;
	if (button == 1)
		a->fractal->cy = (double)y / a->mlx->height * 2 - 1;
	a->fractal->x_min = xm - x * a->fractal->dx;
	a->fractal->x_max = xm + (a->mlx->width - x) * a->fractal->dx;
	a->fractal->y_min = ym - y * a->fractal->dy;
	a->fractal->y_max = ym + (a->mlx->height - y) * a->fractal->dy;
	update_image(a);
	return (1);
}

static void	subtract(double *a, double b)
{
	*a -= b;
}

static void	add(double *a, double b)
{
	*a += b;
}

static void	apply_step(double *min, double *max, double step,
				void f(double*, double))
{
	f(min, step);
	f(max, step);
}

int	kbd_event(int button, t_all *a)
{
	double	stepx;
	double	stepy;

	ft_putnbr_fd(button, 2);
	stepx = a->fractal->dx * 8;
	stepy = a->fractal->dy * 8;
	if (button == 65363) // 124
		apply_step(&(a->fractal->x_min), &(a->fractal->x_max), stepx, add);
	else if (button == 65361) // 123
		apply_step(&(a->fractal->x_min), &(a->fractal->x_max), stepx, subtract);
	else if (button == 65364) //125
		apply_step(&(a->fractal->y_min), &(a->fractal->y_max), stepy, add);
	else if (button == 65362) // 126
		apply_step(&(a->fractal->y_min), &(a->fractal->y_max), stepy, subtract);
	else if (button == 65307) // 53
	{
		mlx_destroy_image(a->mlx->mlx_ptr, a->mlx->image);
		exit(0);
	}
	else if (button == 15) // ?
		julia(a);
	update_image(a);
	return (1);
}
