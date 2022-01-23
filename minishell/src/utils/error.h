/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:32:43 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:32:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/17/22.
//

#ifndef ERROR_H
# define ERROR_H

int	minish_err(char *err_msg);

int	syntax_error(char *err);

int	cmd_err(char *command);

#endif //ERROR_H
