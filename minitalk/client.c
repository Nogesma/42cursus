/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 01:25:32 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/29 01:27:13 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <signal.h>
#include <stdio.h>

int	send_null(pid_t pid)
{
	static int	j = -1;

	ft_putnbr_fd(0, 2);
	if (++j < 8)
	{
		kill(pid, SIGUSR1);
		return (0);
	}
	j = -1;
	return (1);
}

int	send_signal(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
		return (2);
	return (0);
}

int	send_str(char *s, pid_t p)
{
	static char		*str = 0;
	static int		i = -1;
	static pid_t	pid = 0;

	if (s)
		str = ft_strdup(s);
	if (!str)
		return (2);
	if (!pid)
		pid = p;
	if (str[++i / 8])
	{
		ft_putnbr_fd((str[i / 8] & (0x80 >> (i % 8))) > 0, 2);
		if (str[i / 8] & (0x80 >> (i % 8)))
			return (send_signal(pid, SIGUSR2));
		return (send_signal(pid, SIGUSR1));
	}
	if (send_null(pid))
	{
		free(str);
		return (1);
	}
	return (0);
}

void	catch(__attribute__((unused)) int sig)
{
	int	i;

	i = send_str(0, 0);
	if (i == 1)
		exit(0);
	if (i == 2)
	{
		ft_putendl_fd("Error sending signal to server. "
			"Are you sure it is running?", 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	if (argc == 3)
	{
		signal(SIGUSR1, catch);
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			return (1);
		send_str(argv[2], pid);
		while (1)
			pause();
	}
	else
	{
		ft_putendl_fd("usage: client [pid] [string]", 2);
		return (1);
	}
}
