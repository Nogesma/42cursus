#include <libft.h>
#include <signal.h>

void send_str(char *s, pid_t pid)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = 8;
		while (--j >= 0)
		{
			if (s[i] & (1 << j))
			{
				ft_putchar_fd('1', 1);
				kill(pid, SIGUSR2);
				pause();
			}
			else
			{
				ft_putchar_fd('0', 1);
				kill(pid, SIGUSR1);
				pause();
			}
		}
	}
}
void resume(int i)
{
	return ;
}

int main(int argc, char **argv)
{
	pid_t	pid;
	signal(SIGCONT, resume);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_str(argv[2], pid);
	}
}
