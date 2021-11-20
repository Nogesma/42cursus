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

void	wait_thread_exit(t_philosophers *p, t_params *params)
{
	int	i;

	i = -1;
	while (++i < params->number_of_philosophers)
	{
		pthread_join(p[i].thread_id, NULL);
		pthread_mutex_destroy(&(params->mutex[i]));
		pthread_mutex_destroy(&(params->time_mutex[i]));
	}
	pthread_mutex_destroy(&(params->print_mutex));
	free(params->mutex);
	free(params->time_mutex);
	free(p);
}

int	main(int ac, char **av)
{
	t_params		params;
	t_philosophers	*philosophers;

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
	if (check_params(&params))
		return (1);
	params.ded = 0;
	gettimeofday(&(params.start_time), NULL);
	create_mutex(&params);
	philosophers = create_philosophers(&params);
	check_end(&params, philosophers);
	wait_thread_exit(philosophers, &params);
}
