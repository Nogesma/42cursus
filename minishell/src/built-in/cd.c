/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:06:49 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:06:52 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>

#include "export.h"

int	cd(char **args, t_list **env)
{
	char	*old_pwd;
	char	*pwd;
	char	*lst[3];

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (-1);
	if (chdir(args[0]) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("minish: cd: ", 2);
		perror(args[1]);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	lst[0] = ft_strjoin("PWD=", pwd);
	if (!lst[0])
		return (-1);
	lst[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (!lst[1])
		return (-1);
	lst[2] = NULL;
	free(pwd);
	free(old_pwd);
	export(lst, env);
	free(lst[0]);
	free(lst[1]);
	return (0);
}
