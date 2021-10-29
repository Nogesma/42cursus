/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <msegrans@student.42lausanne.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 01:27:22 by marvin            #+#    #+#             */
/*   Updated: 2021/10/29 01:27:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <signal.h>
#include <stdio.h>

void	write_char(const char *s)
{
	char	c;
	int		i;

	i = 0;
	c = 0;
	while (s[i])
	{
		c *= 2;
		c += s[i] - '0';
		++i;
	}
	ft_putchar_fd((char)c, 1);
}

void	print_signal(char c)
{
	static char	buffer[9];
	int			i;

	i = 0;
	while (buffer[i])
		i++;
	if (i != 7)
		buffer[i] = c;
	else
	{
		buffer[i] = c;
		write_char(buffer);
		ft_bzero(buffer, 9);
	}
}

void	handler(int sig, siginfo_t *info,
	__attribute__((unused)) void *context)
{
	if (sig == SIGUSR1)
		print_signal('0');
	else
		print_signal('1');
	usleep(250);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	usraction;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	usraction.sa_flags = SA_SIGINFO;
	usraction.sa_sigaction = handler;
	sigfillset(&usraction.sa_mask);
	if (sigaction(SIGUSR1, &usraction, NULL) == -1)
		ft_putstr_fd("Error, could not process SIGUSR1", 2);
	if (sigaction(SIGUSR2, &usraction, NULL) == -1)
		ft_putstr_fd("Error, could not process SIGUSR2", 2);
	while (1)
		pause();
}
