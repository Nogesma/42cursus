/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:14:34 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 01:14:35 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <semaphore.h>

typedef struct params
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct timeval	start_time;
	sem_t			*sem;
	sem_t			*print;
}	t_params;

typedef struct philosophers
{
	struct timeval	last_meal;
	int				number_of_meals;
	t_params		*params;
	int				n;
	pid_t			pid;
}	t_philosophers;

#endif //TYPES_H
