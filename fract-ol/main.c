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

int	error(void)
{
	ft_putendl_fd("usage: fractol [mandelbrot/julia] {-1.0/1.0} {-1.0/1.0}", 1);
	return (1);
}

void	start_hooks(t_all *all)
{
	mlx_mouse_hook(all->mlx->mlx_win, &mouse_event, all);
	mlx_hook(all->mlx->mlx_win, 6, 1L << 8, &click_and_drag, all);
	mlx_hook(all->mlx->mlx_win, 5, 1L << 3, &release, all);
	mlx_key_hook(all->mlx->mlx_win, &kbd_event, all);
	mlx_loop(all->mlx->mlx_ptr);
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
			return (error());
		start_hooks(all);
	}
	return (error());
}
