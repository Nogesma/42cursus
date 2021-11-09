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

int	mouse_event(int button, int x, int y, all_t *a)
{
	double	xm;
	double	ym;

	xm = a->fractal->dx * x + a->fractal->xMin;
	ym = a->fractal->dy * y + a->fractal->yMin;
	if (button == 4)
	{
		a->fractal->dx /= a->fractal->zoom;
		a->fractal->dy /= a->fractal->zoom;
	}
	else if (button == 5)
	{
		a->fractal->dx *= a->fractal->zoom;
		a->fractal->dy *= a->fractal->zoom;
	}
	a->fractal->xMin = xm - x * a->fractal->dx;
	a->fractal->xMax = xm + (a->mlx->width - x) * a->fractal->dx;
	a->fractal->yMin = ym - y * a->fractal->dy;
	a->fractal->yMax = ym + (a->mlx->height - y) * a->fractal->dy;
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

int	kbd_event(int button, all_t *a)
{
	double	stepx;
	double	stepy;

	stepx = a->fractal->dx * 8;
	stepy = a->fractal->dy * 8;
	if (button == 65363) // 124
		apply_step(&(a->fractal->xMin), &(a->fractal->xMax), stepx, add);
	else if (button == 65361) // 123
		apply_step(&(a->fractal->xMin), &(a->fractal->xMax), stepx, subtract);
	else if (button == 65364) //125
		apply_step(&(a->fractal->yMin), &(a->fractal->yMax), stepy, add);
	else if (button == 65362) // 126
		apply_step(&(a->fractal->yMin), &(a->fractal->yMax), stepy, subtract);
	else if (button == 65307) // 53
	{
		mlx_destroy_image(a->mlx->mlx_ptr, a->mlx->image);
		exit(0);
	}
	update_image(a);
	return (1);
}
