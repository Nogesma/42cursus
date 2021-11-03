#include <signal.h>
#include "libft/libft.h"
#include <stdio.h>

void    sendchar(char c, int pid)
{
	int    i;

	i = 8;
	while (--i >= 0)
	{
		if ((c >> i) & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(50);
	}
}

int    main(int argc, char *argv[])
{
	int    pid;
	int    i;

	if (argc != 3)
	{
		ft_putstr_fd("Error\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i])
		sendchar(argv[2][i], pid);
	i = -1;
	while (++i < 8)
		sendchar(0, pid);
}
