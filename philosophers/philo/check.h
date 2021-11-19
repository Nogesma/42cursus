/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:17:57 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 01:17:58 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H

# include <pthread.h>
# include <sys/time.h>

# include "types.h"
# include "mutex.h"

int		check_params(t_params *p);

void	check_end(t_params *params, t_philosophers *philosophers);

#endif //CHECK_H
