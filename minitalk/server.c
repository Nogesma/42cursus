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

char	*stradd(char *s1, char c)
{
	int		s1l;
	char	*str;

	if (!s1)
	{
		str = (char *)malloc(2 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = c;
		str[1] = 0;
		return (str);
	}
	s1l = ft_strlen(s1);
	str = (char *)malloc((s1l + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1l + 1);
	str[s1l] = c;
	str[s1l + 1] = 0;
	free(s1);
	return (str);
}

void	print_signal(char c)
{
	static char	*str = 0;
	static char	buffer = 0;
	static int	i = 0;

	buffer = buffer << 1 | c;
	i++;
	if (i == 8)
	{
		if (buffer)
			str = stradd(str, buffer);
		else
		{
			ft_putstr_fd(str, 1);
			free(str);
			str = 0;
		}
		buffer = 0;
		i = 0;
	}
}

void	handler(int sig, __attribute__((unused)) siginfo_t *info,
	__attribute__((unused)) void *context)
{
	if (sig == SIGUSR1)
		print_signal(0);
	else if (sig == SIGUSR2)
		print_signal(1);
	else
		exit(1);
//	if (kill(info->si_pid, SIGUSR1) == -1)
//	{
//		ft_putstr_fd("Error sending sigusr1\n", 2);
//		exit(1);
//	}
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
