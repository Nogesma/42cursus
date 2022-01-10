/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:48:06 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:48:10 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include <libft.h>

t_list	*get_env(t_list **env, char *name);

char	*get_env_content(t_list **env, char *name);

#endif //ENVIRON_H
