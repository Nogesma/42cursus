/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 00:43:26 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/19 00:43:27 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

typedef struct s_pipe
{
	int	token;
	int	in[2];
	int	out[2];
}	t_pipe;

int		mpipe(t_pipe *fd);
void	close_pipes(int fd[2]);
void	init_pipe_data(t_pipe *fd, t_pipe *data);
void	restore_fd(t_pipe *fd, int saved_fd[2]);

#endif //PIPES_H
