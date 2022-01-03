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

#include "built_ins.h"

void	cd(char **args, t_list **env)
{
	char	*old_pwd;
	char	*pwd;
	char	*lst[3];

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	if (chdir(args[0]) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("minish: cd: ", 2);
		perror(args[1]);
		status_code(1, 1);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	lst[0] = ft_strjoin("PWD=", pwd);
	if (!lst[0])
		return ;
	lst[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (!lst[1])
		return ;
	lst[2] = NULL;
	free(pwd);
	free(old_pwd);
	export(lst, env);
	free(lst[0]);
	free(lst[1]);
	status_code(1, 0);
}
