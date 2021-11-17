/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:40:34 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/17 10:40:36 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include <stdlib.h>
#include <sys/time.h>

typedef struct params
{
  int	number_of_philosophers;
  int	time_to_die;
  int	time_to_eat;
  int	time_to_sleep;
  int	number_of_times_each_philosopher_must_eat;
  struct timeval start_time;
  int ded;
  pthread_mutex_t *mutex;
  pthread_mutex_t print_mutex;
  pthread_mutex_t *time_mutex;
} params_t;

typedef struct philosophers
{
  struct timeval last_meal;
  params_t *params;
  int n;
  pthread_t thread_id;
} philosophers_t;

void print_timestamp(struct timeval t, int n, char *s, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	printf("%lu %d %s\n", t.tv_sec * 1000 + t.tv_usec / 1000, n, s);
	pthread_mutex_unlock(m);
}

void do_action(philosophers_t *p, char *s, int n)
{
	struct timeval t;

	if (p->params->ded)
		return ;
	gettimeofday(&t, NULL);
	print_timestamp(t, p->n, s, &(p->params->print_mutex));
	usleep(n * 1000);
}

void print_look(int a, int b, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	printf("%d looking at fork %d\n", a, b);
	pthread_mutex_unlock(m);
}

void take_forks(philosophers_t *p)
{
	if (p->n % 2)
	{
		print_look(p->n, p->n, &(p->params->print_mutex));
		pthread_mutex_lock(&(p->params->mutex[p->n]));
		do_action(p, "has taken a fork", 0);
		print_look(p->n, (p->n + 1) % p->params->number_of_philosophers, &(p->params->print_mutex));
		pthread_mutex_lock(&(p->params->mutex[(p->n + 1) % p->params->number_of_philosophers]));
		do_action(p, "has taken a fork", 0);
	}
	else
	{

		print_look(p->n, (p->n + 1) % p->params->number_of_philosophers, &(p->params->print_mutex));
		pthread_mutex_lock(&(p->params->mutex[(p->n + 1) % p->params->number_of_philosophers]));
		do_action(p, "has taken a fork", 0);
		if (p->params->number_of_philosophers <= 1)
		{
			pthread_mutex_unlock(&(p->params->mutex[(p->n + 1) % p->params->number_of_philosophers]));
			return ;
		}
		print_look(p->n, p->n, &(p->params->print_mutex));
		pthread_mutex_lock(&(p->params->mutex[p->n]));
		do_action(p, "has taken a fork", 0);
	}
}

void release_forks(philosophers_t *p)
{
	pthread_mutex_unlock(&(p->params->mutex[p->n]));
	if (p->n + 1 == p->params->number_of_philosophers)
		pthread_mutex_unlock(&(p->params->mutex[0]));
	else
		pthread_mutex_unlock(&(p->params->mutex[p->n + 1]));
}

void *eat_think_sleep_die(void *ptr)
{
	philosophers_t *philo;

	philo = (philosophers_t *)ptr;
//	printf("Hello from thread: %d at pid %d\n", philo->n, getpid());
	if (philo->n % 2)
		usleep((philo->params->time_to_sleep + philo->params->time_to_eat) / 2);
	while (1)
	{
		if (philo->params->ded)
			return (NULL);
		take_forks(philo);
		if (philo->params->number_of_philosophers <= 1)
			return (NULL);
		do_action(philo, "is eating", philo->params->time_to_eat);
		pthread_mutex_lock(&(philo->params->time_mutex[philo->n]));
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&(philo->params->time_mutex[philo->n]));
		release_forks(philo);
		do_action(philo, "is sleeping", philo->params->time_to_sleep);
		do_action(philo, "is thinking", 0);
	}
}

void create_mutex(params_t *args)
{
	int i;

	args->mutex = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	args->time_mutex = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	i = -1;
	while (++i < args->number_of_philosophers)
	{
		pthread_mutex_init(&(args->mutex[i]), NULL);
		pthread_mutex_init(&(args->time_mutex[i]), NULL);
	}
	pthread_mutex_init(&(args->print_mutex), NULL);
}

void	init_philo(philosophers_t *p, params_t *params, int i)
{
	p->params = params;
	p->n = i;
	p->last_meal.tv_usec = params->start_time.tv_usec;
	p->last_meal.tv_sec = params->start_time.tv_sec;
}

philosophers_t	*create_philosophers(params_t *args)
{
	int i;
	philosophers_t *philosophers;

	philosophers = malloc(sizeof(philosophers_t) * args->number_of_philosophers);

	i = -1;
	while (++i < args->number_of_philosophers)
	{
		init_philo(&(philosophers[i]), args, i);
		pthread_create(&(philosophers[i].thread_id), NULL, eat_think_sleep_die, &(philosophers[i]));
	}
	return (philosophers);
}

int is_dead(philosophers_t *p)
{
	struct timeval t;
	long now;
	long time_to_die;



	pthread_mutex_lock(&(p->params->time_mutex[p->n]));
	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	time_to_die = p->last_meal.tv_sec * 1000 + p->last_meal.tv_usec / 1000 + p->params->time_to_die;
	pthread_mutex_unlock(&(p->params->time_mutex[p->n]));
//	printf("%ld %ld %ld\n", now, time_to_die, now - time_to_die);
	if (time_to_die < now)
		return (1);
	return (0);
}

void wait_thread_exit(philosophers_t *p)
{
	int i;

	i = -1;
	while (++i < p->params->number_of_philosophers)
		pthread_join(p[i].thread_id, NULL);
}

int main(int ac, char **av)
{
	params_t params;
	philosophers_t *philosophers;

	if (ac < 5)
		return (1);
	params.number_of_philosophers = ft_atoi(av[1]);
	params.time_to_die = ft_atoi(av[2]);
	params.time_to_eat = ft_atoi(av[3]);
	params.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		params.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		params.number_of_times_each_philosopher_must_eat = -1;

	params.ded = 0;
	gettimeofday(&(params.start_time), NULL);
	create_mutex(&params);
	philosophers = create_philosophers(&params);

	while (1)
	{
		ac = -1;
		while (++ac < params.number_of_philosophers)
		{
			if (is_dead(&(philosophers[ac])))
			{
				do_action(&philosophers[ac], "died", 0);
				params.ded = 1;
				wait_thread_exit(philosophers);
				return (0);
			}
		}
		usleep(5000);
	}
}
