/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:56 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:58 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	exit_cmd(char **args)
{
	int				i;

	ft_printf(STDERR_FILENO, "exit\n");
	if (*args == NULL)
		exit(0);
	i = -1;
	while (args[0][++i])
	{
		if (!ft_isdigit(args[0][i]))
		{
			ft_printf(STDERR_FILENO,
				"minish: exit: %s: numeric argument required", args[0]);
			exit(255);
		}
	}
	if (args[1] != NULL)
	{
		status_code(1, 1);
		return (ft_putendl_fd(
			"minish: exit: too many arguments", STDERR_FILENO));
	}
	i = (unsigned char) ft_atoi(args[0]);
	exit(i);
}
