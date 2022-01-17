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
#include <signal.h>

void	wait_thread_exit(t_philosophers *p, t_params *params)
{
	int		i;
	int		status;
	pid_t	pid;

	i = -1;
	if (p->params->number_of_times_each_philosopher_must_eat == -1)
	{
		pid = wait(&status);
		while (++i < params->number_of_philosophers)
			if (p[i].pid != pid)
				kill(p[i].pid, SIGTERM);
	}
	else
	{
		while (++i < params->number_of_philosophers)
			wait(&status);
	}
	sem_close(params->sem);
	sem_close(params->print);
	sem_unlink("print");
	sem_unlink("forks");
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
	sem_unlink("print");
	sem_unlink("forks");
	params.print = sem_open("print", O_CREAT, S_IWRITE | S_IREAD, 1);
	params.sem = sem_open("forks", O_CREAT,
			S_IWRITE | S_IREAD, params.number_of_philosophers);
	gettimeofday(&(params.start_time), NULL);
	philosophers = create_philosophers(&params);
	wait_thread_exit(philosophers, &params);
}
