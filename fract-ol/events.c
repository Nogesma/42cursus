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

void	mouse_event(int button, int x, int y, all_t *a)
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
}

void	subtract(double *a, double b)
{
	*a -= b;
}

void	add(double *a, double b)
{
	*a += b;
}

void	apply_step(double *min, double *max, double step,
				void *f(double*, double))
{
	f(min, step);
	f(max, step);
}

void	kbd_event(int button, all_t *a)
{
	double	stepx;
	double	stepy;

	stepx = a->fractal->dx * 4;
	stepy = a->fractal->dy * 4;
	if (button == 124)
		apply_step(a->fractal->xMin, a->fractal->xMax, stepx, add);
	else if (button == 123)
		apply_step(a->fractal->xMin, a->fractal->xMax, stepx, subtract);
	else if (button == 125)
		apply_step(a->fractal->yMin, a->fractal->yMax, stepy, add);
	else if (button == 126)
		apply_step(a->fractal->yMin, a->fractal->yMax, stepy, subtract);
	else if (button == 53)
	{
		mlx_destroy_image(a->mlx->mlx_ptr, a->mlx->image);
		exit(0);
	}
	update_image(a);
}
