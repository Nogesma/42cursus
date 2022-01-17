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
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include <sys/errno.h>
#include <string.h>

#include "../utils/environ.h"
#include "export.h"

static int	free_all(void *a, void *b, void *c, void *d)
{
	free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
	return (-1);
}

static int	update_pwd_env(char *pwd, char *old_pwd, t_list **env)
{
	char	*lst[3];

	lst[0] = ft_strjoin("PWD=", pwd);
	if (!lst[0])
		return (free_all(old_pwd, pwd, NULL, NULL));
	lst[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (!lst[1])
		return (free_all(old_pwd, pwd, lst[0], NULL));
	lst[2] = NULL;
	export(lst, env);
	free_all(old_pwd, pwd, lst[0], lst[1]);
	return (0);
}

int	cd(char **args, t_list **env)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (-1);
	if (args[0] == NULL)
		args[0] = ft_strdup(get_env_content(env, "HOME"));
	if (chdir(args[0]) == -1)
	{
		free(old_pwd);
		ft_printf(STDERR_FILENO,
			"minish: cd: %s: %s\n", args[0], strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_all(old_pwd, NULL, NULL, NULL));
	return (update_pwd_env(pwd, old_pwd, env));
}
