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

#include "../parser/cmd_loop.h"
#include "error.h"

/**
 * Executes pipes and redirect if needed
 * **/
int	mpipe(t_pipe *fd)
{
	if (fd->out[0] != fd->out[1])
		close(fd->out[0]);
	if (dup2(fd->out[1], STDOUT_FILENO) == -1)
		return (minish_err("pipe error"));
	if (fd->in[0] != fd->in[1])
		close(fd->in[1]);
	if (dup2(fd->in[0], STDIN_FILENO) == -1)
		return (minish_err("pipe error"));
	return (0);
}

/**
 * Close fds if needed. We do not want to close fds if they are
 * stdin, out or err.
 * We also do not want to close it twice if it represent the same file.
 * **/
void	close_pipes(int fd[2])
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2 && fd[1] != fd[0])
		close(fd[1]);
}

void	init_pipe_data(t_pipe *fd, t_pipe *data)
{
	fd->token = -1;
	fd->out[0] = data->out[0];
	fd->out[1] = data->out[1];
	fd->in[0] = data->in[0];
	fd->in[1] = data->in[1];
}
