/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:41:22 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/10 15:41:23 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include "types.h"
# include "tools.h"

int	mandelbrot(t_all *a);

int	julia(t_all *a);

#endif //FRACTAL_H
