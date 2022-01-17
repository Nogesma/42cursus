/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:32:39 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:32:42 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tadeusz Kondracki on 1/17/22.
//

#include <stdio.h>

int	ft_perror(char *err_msg)
{
	perror(err_msg);
	return (1);
}
