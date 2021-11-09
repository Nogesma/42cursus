/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:34:20 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:34:23 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		*buffer;
	char	*image;
	int		height;
	int		width;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
}	t_mlx;

typedef struct fract
{
	double	zoom;
	double	dx;
	double	dy;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
}	t_fract;

typedef struct colour
{
	int	sr;
	int	sg;
	int	sb;
	int	er;
	int	eg;
	int	eb;
}	t_colour;

typedef struct all
{
	t_mlx		*mlx;
	t_colour	*colour;
	t_fract		*fractal;
}	t_all;

#endif //TYPES_H
