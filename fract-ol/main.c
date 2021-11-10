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

int	update_image(t_all *a)
{
	int	x;
	int	y;
	int	iter;
	int *func;


	iter = (int)(200 / sqrt(2.0 * fabs(a->fractal->y_min - a->fractal->y_max)));
	#pragma omp parallel for private(x)
	for (y = 0; y < a->mlx->height; y++)
		for (x = 0; x < a->mlx->width; x++)
		{
			a->mlx->buffer[y * a->mlx->width + x]
				= func[a->fractal->t](iter,
					(a->fractal->dx * x) + a->fractal->x_min,
					(a->fractal->dy * y) + a->fractal->y_min, a);
		}
	mlx_put_image_to_window(a->mlx->mlx_ptr, a->mlx->mlx_win,
		a->mlx->image, 0, 0);

	return (1);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "julia", 5) == 0)
		{
			if (argc > 3)
				all = init(1, ft_atod(argv[2]), ft_atod(argv[3]));
			else
				all = init(1, -0.8, 0.156);
			julia(all);
		}
		else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		{
			all = init(0, 0, 0);
			mandelbrot(all);
		}
		else
			return (1);
		mlx_mouse_hook(all->mlx->mlx_win, &mouse_event, all);
		mlx_key_hook(all->mlx->mlx_win, &kbd_event, all);
		mlx_loop(all->mlx->mlx_ptr);
	}
	ft_putendl_fd("usage: fractol [mandelbrot/julia] {-1.0/1.0} {-1.0/1.0}", 1);
	return (1);
}
