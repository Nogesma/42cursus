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

int	update_image(t_all *a)
{
	int	x;
	int	y;
	int	iter;
	int	px;
	int	(*func[2])(int maxiter, double x0, double y0, t_all *a);

	func[0] = iterate_mandelbrot;
	func[1] = iterate_julia;
	iter = (int)(200 / sqrt(2.0 * fabs(a->fractal->y_min - a->fractal->y_max)));
	y = -1;
	px = 0;
	while (++y < a->mlx->height)
	{
		x = -1;
		while (++x < a->mlx->width)
		{
			a->mlx->buffer[px++]
				= func[a->fractal->t](iter,
					(a->fractal->dx * x) + a->fractal->x_min,
					(a->fractal->dy * y) + a->fractal->y_min, a);
		}
	}
	mlx_put_image_to_window(a->mlx->mlx_ptr, a->mlx->mlx_win,
		a->mlx->image, 0, 0);
	return (1);
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
			void f(double*, double))
{
	f(min, step);
	f(max, step);
}
