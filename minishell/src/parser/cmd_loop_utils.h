/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_loop_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:33:15 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/20 14:33:16 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 19.01.22.
//

#ifndef CMD_LOOP_UTILS_H
# define CMD_LOOP_UTILS_H

int	find_token(char *line, char **cmd_two);
int	check_parenthesis(char **line);

#endif //CMD_LOOP_UTILS_H
