/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:54 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:55 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	echo(char **args)
{
	int	newline;

	newline = 1;
	if (!*args)
		return ;
	if (!ft_strncmp("-n", args[0], 3))
	{
		newline = 0;
		args++;
	}
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	status_code(1, 0);
}
