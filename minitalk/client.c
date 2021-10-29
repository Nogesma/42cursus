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

void	send_str(char *s, pid_t pid)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = 7;
		while (j >= 0)
		{
			if (s[i] & (1 << j))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			pause();
			j--;
		}
	}
}

void	catch(__attribute__((unused)) int sig,
	__attribute__((unused)) siginfo_t *info,
	__attribute__((unused)) void *context)
{
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	resume;

	resume.sa_sigaction = catch;
	resume.sa_flags = 0;
	sigfillset(&resume.sa_mask);
	if (sigaction(SIGUSR1, &resume, NULL) == -1)
		ft_putstr_fd("Error, could not process SIGCONT", 2);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_str(argv[2], pid);
	}
}
