/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:32:21 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/10 15:32:23 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	init_fractal(t_mlx *mlx, int i)
{
	if (i)
	{
		mlx->height = 900;
		mlx->width = 900;
	}
	else
	{
		mlx->height = 896;
		mlx->width = 988;
	}
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
	colour->a = 5;
	colour->b = 12;
	colour->c = 8;
}

t_all	*init(int i, double cx, double cy)
{
	t_all	*all;

	all = get_all();
	if (!all)
		return (NULL);
	all->mlx->mlx_ptr = mlx_init();
	init_fractal(all->mlx, i);
	init_colour(all->colour);
	all->fractal->zoom = 1.1;
	all->fractal->cx = cx;
	all->fractal->cy = cy;
	all->fractal->t = i;
	all->mlx->is_pressed = 0;
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
