/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:38:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/12 15:38:45 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ENV_H
# define PARSE_ENV_H

# include <libft.h>

int		get_env_name_size(const char *s);

void	get_env_size(char *s, t_list **env, int *size, int *i);

int		unpack_env(char *s, char *new, t_list **env, int *i);

#endif //PARSE_ENV_H
