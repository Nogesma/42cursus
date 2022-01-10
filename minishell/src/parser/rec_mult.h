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

int	rec_cmds(char *line, t_list **env, char has_pipes);

#endif //REC_MULT_H
