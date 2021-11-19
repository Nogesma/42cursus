/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:13:42 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 01:13:43 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

# include "types.h"

void	last_action(t_philosophers *p, char *s);

void	do_action(t_philosophers *p, char *s, int n);

void	take_forks(t_philosophers *p);

void	release_forks(t_philosophers *p);

#endif //MUTEX_H
