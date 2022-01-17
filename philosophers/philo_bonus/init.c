/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 00:59:31 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 00:59:36 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"
#include "mutex.h"
#include "check.h"

void	eat_think_sleep_die(t_philosophers	*philo)
{
	if (philo->n % 2 == 0)
		usleep(philo->params->time_to_eat * 900);
	if ((philo->params->number_of_philosophers % 2)
		&& (philo->n + 1 == philo->params->number_of_philosophers))
		usleep(philo->params->time_to_eat * 900);
	while (1)
	{
		take_forks(philo);
		if (philo->params->number_of_philosophers < 2)
			exit(2);
		if (check_dead(philo))
			exit(1);
		gettimeofday(&philo->last_meal, NULL);
		do_action(philo, "is eating", philo->params->time_to_eat);
		philo->number_of_meals++;
		release_forks(philo);
		if (check_eat(philo))
			exit(1);
		do_action(philo, "is sleeping", philo->params->time_to_sleep);
		do_action(philo, "is thinking", 0);
	}
}

void	init_philo(t_philosophers *p, t_params *params, int i)
{
	p->params = params;
	p->n = i;
	p->number_of_meals = 0;
	p->last_meal.tv_usec = params->start_time.tv_usec;
	p->last_meal.tv_sec = params->start_time.tv_sec;
}

t_philosophers	*create_philosophers(t_params *args)
{
	int				i;
	pid_t			child;
	t_philosophers	*philosophers;

	philosophers = malloc(sizeof(t_philosophers)
			* args->number_of_philosophers);
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		init_philo(&(philosophers[i]), args, i);
		child = fork();
		if (child == -1)
			return (NULL);
		if (child == 0)
			eat_think_sleep_die(&(philosophers[i]));
		else
			philosophers[i].pid = child;
	}
	return (philosophers);
}
