#include <libft.h>
#include <signal.h>
#include <stdio.h>

void write_char(const char *s)
{
	int c;
	int	i;

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

void print_signal(char c)
{
	static char buffer[9];
	int i;

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
void usr1_handler(int i, siginfo_t *info, void *context)
{
	print_signal('0');
	kill(info->si_pid, SIGCONT);
}

void usr2_handler(int i, siginfo_t *info, void *context)
{
	print_signal('1');
	kill(info->si_pid, SIGCONT);
}

#include <stdio.h>

int main(void)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);

	struct sigaction usr1_action;
	struct sigaction usr2_action;

	usr1_action.sa_flags = SA_SIGINFO;
	usr2_action.sa_flags = SA_SIGINFO;

	usr1_action.sa_sigaction = usr1_handler;
	usr2_action.sa_sigaction = usr2_handler;

	sigfillset(&usr1_action.sa_mask);
	sigfillset(&usr2_action.sa_mask);


	sigaction(SIGUSR1, &usr1_action, NULL);
	sigaction(SIGUSR2, &usr2_action, NULL);
	while (1)
		;
}
