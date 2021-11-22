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

#include "mutex.h"

void	do_action(t_philosophers *p, char *s, int n)
{
	struct timeval	t;

	if (p->params->ded)
		return ;
	gettimeofday(&t, NULL);
	pthread_mutex_lock(&(p->params->print_mutex));
	printf("%ld %d %s\n",
		time_to_ms(t) - time_to_ms(p->params->start_time), p->n + 1, s);
	pthread_mutex_unlock(&(p->params->print_mutex));
	usleep(n * 1000);
}

void	take_forks(t_philosophers *p)
{
	pthread_mutex_lock(&(p->params->mutex[p->n]));
	do_action(p, "has taken a fork", 0);
	if (p->n < 2)
		return ;
	pthread_mutex_lock(&(p->params->mutex[(p->n + 1)
			% p->params->number_of_philosophers]));
	do_action(p, "has taken a fork", 0);
}

void	release_forks(t_philosophers *p)
{
	pthread_mutex_unlock(&(p->params->mutex[p->n]));
	pthread_mutex_unlock(&(p->params->mutex[(p->n + 1)
			% p->params->number_of_philosophers]));
}
