/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:50:18 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:50:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * If stdin is not a tty, we need to set the prompt to an empty string and set
 * term attributes to not echo stdin (<--TODO).
 * Otherwise we just set the termcaps to not display ^\
 * */
int	termios_setup(void)
{
	struct termios	cfg;
	int				ttyfd;

	if (isatty(STDIN_FILENO))
		ttyfd = STDIN_FILENO;
	else
		ttyfd = open("/dev/tty", O_NONBLOCK);
	if (ttyfd < 0)
		return (-1);
	if (tcgetattr(ttyfd, &cfg) < 0)
		return (-1);
	if (ttyfd == STDIN_FILENO)
		cfg.c_lflag &= ~ECHOCTL;
	else
		cfg.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(ttyfd, TCSADRAIN, &cfg) < 0)
		return (-1);
	return (ttyfd);
}
