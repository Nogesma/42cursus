/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:47:47 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:47:48 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <libft.h>
# include "../parser/cmd_loop.h"

int	search_exec(char *line, t_list **env, t_pipe *fd);

#endif //EXEC_H
