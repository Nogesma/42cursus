/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:26 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:29 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft.h>

t_list			*get_env(t_list **env, char *name);

char			*get_env_content(t_list **env, char *name);

unsigned char	status_code(unsigned char set, unsigned char n);

unsigned char	is_fork(unsigned char set, unsigned char n);

#endif