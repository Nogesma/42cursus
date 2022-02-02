/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:33:43 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 23:33:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 26.12.21.
//

#include <libft.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "../exec/exec.h"
#include "cmd_loop.h"
#include "../utils/global.h"
#include "../utils/error.h"
#include "redirect.h"
#include "cmd_loop_utils.h"

//sets any < > << >> redirects, while saving current fd and restoring
//after it exec. If parenthesis are present, recursively calls cmd_loop
//on the subset of commands
static int	cmds_redirect(char *line, t_list **env, t_pipe *fd)
{
	int	save_fdout[2];
	int	forks;

	save_fdout[0] = fd->out[0];
	save_fdout[1] = fd->out[1];
	if (check_parenthesis(&line))
		return (cmds_loop(line, env, fd));
	if (fd->out[0] != fd->out[1] || fd->in[0] != fd->in[1])
		fd->token = 2;
	if (set_redirects(line, env, fd))
	{
		status_code(1, 1);
		return (0);
	}
	forks = search_exec(line, env, fd);
	if (fd->out[0] != save_fdout[0])
		close(fd->out[0]);
	fd->out[0] = save_fdout[0];
	fd->out[1] = save_fdout[1];
	return (forks);
}

//wait *forks times and updates status code if needed
void	wait_forks(int *forks)
{
	int	status;

	status = -1;
	while ((*forks)-- > 0)
		wait(&status);
	*forks = 0;
	is_fork(1, 0);
	if (status != -1 && status_code(0, 0) != 130 && WIFEXITED(status))
		status_code(1, WEXITSTATUS(status));
}

//sets/resets pipe redirects if any and waits for forked cmd if needed
static int	do_cmds(t_cmdinput cmd, t_pipe *fd, int *forks, t_pipe *data)
{
	fd->out[0] = data->out[0];
	fd->out[1] = data->out[1];
	if (fd->token == 2)
	{
		if (pipe(fd->out) == -1)
			return (minish_err("pipe error"));
		*forks += cmds_redirect(cmd.line, cmd.env, fd);
		close_pipes(fd->in);
		fd->in[0] = fd->out[0];
		fd->in[1] = fd->out[1];
	}
	else
	{
		*forks += cmds_redirect(cmd.line, cmd.env, fd);
		close_pipes(fd->in);
		wait_forks(forks);
		fd->in[0] = data->in[0];
		fd->in[1] = data->in[1];
	}
	return (0);
}

//creates new set of pipes from parent set. Then loops over cmds in
//line, finding separating tokens | || &&, executing cmds
//and finally closing pipe
int	cmds_loop(char *line, t_list **env, t_pipe *data)
{
	char		*cmd_two;
	t_pipe		fd;
	int			forks;
	t_cmdinput	cmd;

	cmd.line = line;
	cmd.env = env;
	forks = 0;
	init_pipe_data(&fd, data);
	fd.token = find_token(cmd.line, &cmd_two);
	while (fd.token >= 0)
	{
		do_cmds(cmd, &fd, &forks, data);
		if ((status_code(0, 0) && fd.token == 0)
			|| (!status_code(0, 0) && fd.token == 1))
			return (forks);
		cmd.line = cmd_two;
		fd.token = find_token(cmd.line, &cmd_two);
	}
	fd.out[0] = data->out[0];
	fd.out[1] = data->out[1];
	forks += cmds_redirect(cmd.line, cmd.env, &fd);
	close_pipes(fd.in);
	return (forks);
}
