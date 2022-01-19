/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:33:48 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 23:33:51 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_LOOP_H
# define CMD_LOOP_H

# include <libft.h>

# include "../utils/pipes.h"

typedef struct s_cmdinput
{
	char	*line;
	t_list	**env;
}	t_cmdinput;

int		cmds_loop(char *line, t_list **env, t_pipe *data);
void	wait_forks(int *forks);

#endif //CMD_LOOP_H
