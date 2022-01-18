/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_mult.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:33:48 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 23:33:51 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REC_MULT_H
# define REC_MULT_H

# include <libft.h>

typedef struct s_pipe
{
	int	token;
	int	in[2];
	int	out[2];
}	t_pipe;

int		cmds_loop(char *line, t_list **env);
void	wait_forks(int *forks);

#endif //REC_MULT_H
