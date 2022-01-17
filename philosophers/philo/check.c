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
	long			sec;
	long			usec;

	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	pthread_mutex_lock(&(p->params->time_mutex[p->n]));
	sec = p->last_meal.tv_sec;
	usec = p->last_meal.tv_usec;
	pthread_mutex_unlock(&(p->params->time_mutex[p->n]));
	time_to_die = sec * 1000 + usec / 1000 + p->params->time_to_die;
	if (time_to_die < now)
		return (1);
	return (0);
}

int	check_eat(t_philosophers *p)
{
	int	i;
	int	j;

	if (p->params->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	i = -1;
	j = 0;
	while (++i < p->params->number_of_philosophers)
		if (p[i].number_of_meals
			>= p->params->number_of_times_each_philosopher_must_eat)
			j++;
	return (j == p->params->number_of_philosophers);
}

int	check_params(t_params *p)
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

void	check_end(t_params *params, t_philosophers *philosophers)
{
	int				i;
	struct timeval	t;
	long			timestamp;

	while (1)
	{
		params->ded = (params->ded || check_eat(philosophers));
		if (params->ded)
			return ;
		i = -1;
		while (++i < params->number_of_philosophers)
		{
			if (check_dead(&(philosophers[i])))
			{
				pthread_mutex_lock(&(params->print_mutex));
				gettimeofday(&t, NULL);
				timestamp = time_to_ms(t) - time_to_ms(params->start_time);
				params->ded = 1;
				printf("%lu %d died\n", timestamp, i + 1);
				pthread_mutex_unlock(&(params->print_mutex));
				return ;
			}
		}
		usleep(5000);
	}
}
