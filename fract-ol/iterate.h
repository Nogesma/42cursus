/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:28:05 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/10 15:28:07 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATE_H
# define ITERATE_H

# include "types.h"
# include "tools.h"

unsigned int	iterate_mandelbrot(int maxiter, double x0, double y0, t_all *a);

unsigned int	iterate_julia(int maxiter, double zx, double zy, t_all *a);

#endif //ITERATE_H
