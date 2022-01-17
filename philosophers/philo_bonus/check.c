/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:17:52 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 01:17:56 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"
#include <string.h>

int	check_eat(t_philosophers *p)
{
	if (p->params->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	if (p->number_of_meals
		>= p->params->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

int	check_dead(t_philosophers *p)
{
	struct timeval	t;
	long			now;
	long			time_to_die;

	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	time_to_die = p->last_meal.tv_sec * 1000
		+ p->last_meal.tv_usec / 1000 + p->params->time_to_die;
	if (time_to_die < now)
	{
		sem_wait(p->params->print);
		printf("%ld %d died\n",
			time_to_ms(t) - time_to_ms(p->params->start_time), p->n + 1);
		return (1);
	}
	return (0);
}

int     check_params(t_params *p)
{
	if (p->number_of_philosophers < 0)
		return (1);
	if (p->time_to_die < 1)
		return (1);
	if (p->time_to_eat < 1)
		return (1);
	if (p->time_to_sleep < 1)
		return (1);
	if (p->number_of_times_each_philosopher_must_eat < -1)
		return (1);
	return (0);
}