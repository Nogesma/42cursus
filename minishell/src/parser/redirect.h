/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:29:21 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:29:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/13/22.
//

#ifndef REDIRECT_H
# define REDIRECT_H

# include <libft.h>

# include "cmd_loop.h"

int	set_redirects(char *line, t_list **env, t_pipe *fd);

#endif //REDIRECT_H
