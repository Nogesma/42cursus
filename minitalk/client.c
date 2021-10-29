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

int	send_str(char *s, pid_t p)
{
	static char *str = 0;
	static int	i = -1;
	static int	j = -1;
	static pid_t pid = 0;

	if (s)
		str = ft_strdup(s);
	if (!str)
		return (2);
	if (!pid)
		pid = p;
	if (str[++i / 8])
	{
		if (str[i / 8] & (0x80 >> (i % 8)))
		{
			if (kill(pid, SIGUSR2) == -1)
				return (2);
		}
		else if (kill(pid, SIGUSR1) == -1)
				return (2);
		return (0);
	}
	if (++j < 8)
	{
		kill(pid, SIGUSR1);
		return (0);
	}
	free(str);
	return (1);
}

void	catch(__attribute__((unused)) int sig)
{
	int i;
	i = send_str(0, 0);
	if (i == 2 || i == 1)
	{
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	signal(SIGUSR1, catch);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_str(argv[2], pid);
	}
	while (1)
		pause();
}
