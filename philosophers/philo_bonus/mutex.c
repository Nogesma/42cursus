/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:13:39 by msegrans          #+#    #+#             */
/*   Updated: 2021/11/19 01:13:40 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

#include "types.h"
#include "utils.h"

void	do_action(t_philosophers *p, char *s, int n)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	sem_wait(p->params->print);
	printf("%ld %d %s\n",
		time_to_ms(t) - time_to_ms(p->params->start_time), p->n + 1, s);
	sem_post(p->params->print);
	usleep(n * 1000);
}

void	take_forks(t_philosophers *p)
{
	sem_wait(p->params->sem);
	do_action(p, "has taken a fork", 0);
	if (p->params->number_of_philosophers < 2)
		return ;
	sem_wait(p->params->sem);
	do_action(p, "has taken a fork", 0);
}

void	release_forks(t_philosophers *p)
{
	sem_post(p->params->sem);
	sem_post(p->params->sem);
}
