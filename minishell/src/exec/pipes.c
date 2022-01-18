/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:43:23 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/19 00:43:25 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../parser/rec_mult.h"

void	mpipe(t_pipe *fd)
{
	if (fd->out[0] != fd->out[1])
	{
		close(fd->out[0]);
		dup2(fd->out[1], STDOUT_FILENO);
	}
	if (fd->in[0] != fd->in[1])
	{
		close(fd->in[1]);
		dup2(fd->in[0], STDIN_FILENO);
	}
}
