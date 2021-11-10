/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 03:49:45 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/08 03:49:47 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <omp.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# include "libft/libft.h"
# include "tools.h"
# include "events.h"
# include "types.h"
# include "iterate.h"
# include "init.h"
# include "fractal.h"

int	update_image(t_all *a);

#endif //MAIN_H
