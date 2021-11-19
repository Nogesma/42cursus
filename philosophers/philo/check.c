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

int	check_dead(t_philosophers *p)
{
	struct timeval	t;
	long			now;
	long			time_to_die;

	pthread_mutex_lock(&(p->params->time_mutex[p->n]));
	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	time_to_die = p->last_meal.tv_sec * 1000
		+ p->last_meal.tv_usec / 1000 + p->params->time_to_die;
	pthread_mutex_unlock(&(p->params->time_mutex[p->n]));
	if (time_to_die < now)
		return (1);
	return (0);
}

int	check_eat(t_philosophers *p)
{
	int	i;

	if (p->params->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	i = -1;
	while (++i < p->params->number_of_philosophers)
	{
		pthread_mutex_lock(&(p->params->time_mutex[p->n]));
		if (p->number_of_meals
			== p->params->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&(p->params->time_mutex[p->n]));
			return (1);
		}
		pthread_mutex_unlock(&(p->params->time_mutex[p->n]));
	}
	return (0);
}

int	check_params(t_params *p)
{
	if (p->number_of_philosophers < 0)
		return (1);
	if (p->time_to_die < 0)
		return (1);
	if (p->time_to_eat < 0)
		return (1);
	if (p->time_to_sleep < 0)
		return (1);
	if (p->number_of_times_each_philosopher_must_eat < -1)
		return (1);
	return (0);
}

void	check_end(t_params *params, t_philosophers *philosophers)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < params->number_of_philosophers)
		{
			if (check_dead(&(philosophers[i])))
				return (last_action(&philosophers[i], "died"));
			if (check_eat(&(philosophers[i])))
				return (last_action(&philosophers[i], "finished"));
		}
		usleep(5000);
	}
}