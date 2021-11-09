/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:38:40 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:38:41 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int	iterate_mandelbrot(int maxiterations, double x0, double y0,
									t_all *a)
{
//	double	xtemp;
	double	x;
	double	y;
	double	x2;
	double	y2;
	int		iterations;

	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	iterations = 0;
	while (iterations < maxiterations && (x2 + y2 <= 4))
	{
		y = (x + x) * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
		iterations++;
	}
	return (pick_color(maxiterations, iterations, a->colour));
}

//int iterate_julia(int maxiterations, double x0, double y0)
//{
//	int iterations = 0;
//	double xtemp;
//
//	double cy = 0;
//	double cx = 0;
//	while (x0 * x0 + y0 * y0 < 4  &&  iterations < maxiterations)
//	{
//		xtemp = x0 * x0 - x0 * x0;
//		y0 = 2 * x0 * x0  + cy;
//		x0 = xtemp + cx;
//		iterations++;
//	}
//	return (pickColor(maxiterations, iterations));
//}

int	update_image(t_all *a)
{
	int	x;
	int	y;
	int iter;

	iter = (int)(223.0 / sqrt(4.0 * fabs(a->fractal->y_min - a->fractal->y_max)));
	iter = 30;
	ft_putnbr_fd(iter, 1);
	ft_putendl_fd("", 1);
	#pragma omp parallel for private(x)

	for (y = 0; y < a->mlx->height; y++)
		for (x = 0; x < a->mlx->width; x++)
			a->mlx->buffer[y * a->mlx->width + x]
				= (int)iterate_mandelbrot(iter,
					(a->fractal->dx * x) + a->fractal->x_min,
					(a->fractal->dy * y) + a->fractal->y_min, a);
	mlx_put_image_to_window(a->mlx->mlx_ptr, a->mlx->mlx_win,
		a->mlx->image, 0, 0);
	return (1);
}

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
	a->fractal->x_min = -2.0;
	a->fractal->x_max = 0.47;
	a->fractal->y_min = -1.12;
	a->fractal->y_max = 1.12;
	a->fractal->dx = (a->fractal->x_max - a->fractal->x_min) / a->mlx->width;
	a->fractal->dy = (a->fractal->y_max - a->fractal->y_min) / a->mlx->height;
	update_image(a);
	return (1);
}

void	init_fractal(t_mlx *mlx, int i)
{
	(void)i;
	mlx->height = 896;
	mlx->width = 988;
}

t_all	*get_all(void)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (NULL);
	all->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	all->colour = (t_colour *)malloc(sizeof(t_colour));
	all->fractal = (t_fract *)malloc(sizeof(t_fract));
	return (all);
}

void	init_colour(t_colour *colour)
{
	colour->sr = 206;
	colour->sg = 41;
	colour->sb = 0;
	colour->er = 175;
	colour->eg = 206;
	colour->eb = 0;
}

t_all	*init(int i)
{
	t_all	*all;

	all = get_all();
	if (!all)
		return (NULL);
	all->mlx->mlx_ptr = mlx_init();
	init_fractal(all->mlx, i);
	init_colour(all->colour);
	all->fractal->zoom = 1.1;
	if (!(all->mlx->mlx_ptr))
		return (NULL);
	all->mlx->mlx_win = mlx_new_window(all->mlx->mlx_ptr,
			all->mlx->width, all->mlx->height, "Hello world");
	if (!(all->mlx->mlx_win))
		return (NULL);
	all->mlx->image = mlx_new_image(all->mlx->mlx_ptr,
			all->mlx->width, all->mlx->height);
	all->mlx->buffer = (int *)mlx_get_data_addr(all->mlx->image,
			&all->mlx->pixel_bits, &all->mlx->line_bytes, &all->mlx->endian);
	all->mlx->line_bytes /= 4;
	return (all);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc != 2)
	{
		ft_putendl_fd("usage: fractol", 1);
		return (1);
	}
	else
	{
		if (ft_strncmp(argv[1], "julia", 5) == 0)
		{
			all = init(1);
			julia(all);
		}
		else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		{
			all = init(2);
			mandelbrot(all);
		}
		else
			return (1);
		mlx_mouse_hook(all->mlx->mlx_win, &mouse_event, all);
		mlx_key_hook(all->mlx->mlx_win, &kbd_event, all);
		mlx_loop(all->mlx->mlx_ptr);
	}
}
