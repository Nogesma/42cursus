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

typedef struct params
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct timeval	start_time;
	int				ded;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*time_mutex;
}	t_params;

typedef struct philosophers
{
	struct timeval	last_meal;
	int				number_of_meals;
	t_params		*params;
	int				n;
	pthread_t		thread_id;
}	t_philosophers;

#endif //TYPES_H
