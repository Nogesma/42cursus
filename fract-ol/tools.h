/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:26:50 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:26:52 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <libft.h>
# include <math.h>
# include <mlx.h>

# include "types.h"
# include "iterate.h"

double	ft_atod(char *s);

int		update_image(t_all *a);

void	apply_step(double *min, double *max, double step,
			void f(double*, double));

void	subtract(double *a, double b);

void	add(double *a, double b);

#endif //TOOLS_H
