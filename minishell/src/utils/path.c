/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:48:20 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:48:26 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <libft.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "list.h"

/**
 * Same function as ft_strjoin, but appends a '/' char between the two strings.
 * **/
static char	*ft_strjoin_path(char *s1, char *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	str = (char *)ft_calloc(s1l + s2l + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1l + 1);
	str[s1l] = '/';
	ft_strlcpy(str + s1l + 1, s2, s2l + 1);
	return (str);
}

/**
 * Search the dir pointed by path for the executable exec.
 * **/
static char	*search_path(DIR *dir, char *path, char *exec)
{
	struct dirent	*dp;
	struct stat		statbuf;
	size_t			len;
	char			*exec_path;

	len = ft_strlen(exec);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_type != DT_DIR && !ft_strncmp(exec, dp->d_name, len))
		{
			exec_path = ft_strjoin_path(path, exec);
			if (stat(exec_path, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
				return (exec_path);
		}
		dp = readdir(dir);
	}
	return (NULL);
}

/**
 * Search each dir pointed by PATH for the exec.
 * **/
char	*get_exec_path(char *exec, char *PATH)
{
	DIR		*dir;
	char	**paths;
	int		i;
	char	*exec_path;

	if (exec[0] == 0 || PATH == NULL)
		return (NULL);
	paths = ft_split(PATH, ':');
	i = -1;
	exec_path = NULL;
	while (paths[++i] && exec_path == NULL)
	{
		dir = opendir(paths[i]);
		if (dir)
		{
			exec_path = search_path(dir, paths[i], exec);
			closedir(dir);
		}
	}
	free_list(paths, 0);
	return (exec_path);
}
