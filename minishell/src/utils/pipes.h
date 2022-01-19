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

int		mpipe(t_pipe *fd);
void	close_pipes(int fd[2]);
void	init_pipe_data(t_pipe *fd, t_pipe *data);

#endif //PIPES_H
