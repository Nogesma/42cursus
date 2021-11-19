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

#include "init.h"

void	*eat_think_sleep_die(void *ptr)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)ptr;
	if (philo->n % 2)
		usleep(philo->params->time_to_eat * 1000);
	if ((philo->params->number_of_philosophers % 2)
		&& (philo->n + 1 == philo->params->number_of_philosophers))
		usleep(philo->params->time_to_eat * 1000);
	while (1)
	{
		if (philo->params->ded)
			return (NULL);
		take_forks(philo);
		if (philo->params->number_of_philosophers <= 1)
			philo->params->ded = 1;
		pthread_mutex_lock(&(philo->params->time_mutex[philo->n]));
		gettimeofday(&philo->last_meal, NULL);
		philo->number_of_meals++;
		pthread_mutex_unlock(&(philo->params->time_mutex[philo->n]));
		do_action(philo, "is eating", philo->params->time_to_eat);
		release_forks(philo);
		do_action(philo, "is sleeping", philo->params->time_to_sleep);
		do_action(philo, "is thinking", 0);
	}
}

void	create_mutex(t_params *args)
{
	int	i;

	args->mutex = malloc(sizeof(pthread_mutex_t)
			* args->number_of_philosophers);
	args->time_mutex = malloc(sizeof(pthread_mutex_t)
			* args->number_of_philosophers);
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		pthread_mutex_init(&(args->mutex[i]), NULL);
		pthread_mutex_init(&(args->time_mutex[i]), NULL);
	}
	pthread_mutex_init(&(args->print_mutex), NULL);
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
	t_philosophers	*philosophers;

	philosophers = malloc(sizeof(t_philosophers)
			* args->number_of_philosophers);
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		init_philo(&(philosophers[i]), args, i);
		pthread_create(&(philosophers[i].thread_id),
			NULL, eat_think_sleep_die, &(philosophers[i]));
	}
	return (philosophers);
}
