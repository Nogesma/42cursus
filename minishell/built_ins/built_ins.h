/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:36 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:38 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include <libft.h>

void	cd(char **args, t_list **env);

void	echo(char **args);

void	exit_cmd(char **args);

void	export(char **args, t_list **env);

void	pwd(void);

void	unset(char **args, t_list **env);

#endif