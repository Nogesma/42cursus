/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <msegrans@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 01:27:22 by marvin            #+#    #+#             */
/*   Updated: 2021/11/04 19:09:01 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <signal.h>
#include <stdio.h>

int	print_signal(char c)
{
	static char	buffer = 0;
	static int	i = 0;

	buffer = buffer << 1 | c;
	i++;
	if (i == 8)
	{
		i = 0;
		if (buffer)
			ft_putchar_fd(buffer, 1);
		else
			return (1);
		buffer = 0;
	}
	return (0);
}

void	handler(int sig, __attribute__((unused)) siginfo_t *info,
	__attribute__((unused)) void *context)
{
	static int	pid = 0;

	if (!pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
	{
		if (print_signal(0))
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
	}
	else if (sig == SIGUSR2)
		print_signal(1);
	if (kill(pid, SIGUSR1) == -1)
	{
		ft_putstr_fd("Error sending sigusr1\n", 2);
		exit(1);
	}
}

int	main(void)
{
	struct sigaction	usraction;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&usraction.sa_mask);
	usraction.sa_flags = SA_SIGINFO;
	usraction.sa_sigaction = handler;
	sigaction(SIGUSR1, &usraction, NULL);
	sigaction(SIGUSR2, &usraction, NULL);
	while (1)
		pause();
}
