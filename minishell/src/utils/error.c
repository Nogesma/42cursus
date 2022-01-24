/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:32:39 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:32:42 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/17/22.
//

#include <stdio.h>
#include <libft.h>
#include <unistd.h>

#include "global.h"

int	minish_err(char *err_msg)
{
	ft_printf(2, "minish: ");
	perror(err_msg);
	return (1);
}

int	syntax_error(char *err)
{
	return (ft_printf(2,
			"minish: syntax error near unexpected token `%s`\n", err));
}

int	cmd_err(char *command)
{
	if (!(command[0] == '.' || command[0] == '/'))
		ft_printf(STDERR_FILENO,
			"minish: %s: command not found\n", command);
	else
		ft_printf(STDERR_FILENO,
			"minish: %s: No such file or directory\n", command);
	status_code(1, 127);
	return (0);
}
