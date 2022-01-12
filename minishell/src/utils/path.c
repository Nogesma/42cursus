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

#include "list.h"

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

static char	*free_path_search(char *s, DIR *dir)
{
	closedir(dir);
	return (s);
}

static char	*search_path(char *path, char *exec)
{
	DIR				*dir;
	struct dirent	*dp;
	struct stat		statbuf;
	size_t			len;
	char			*exec_path;

	len = ft_strlen(exec);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	dp = readdir(dir);
	while (dp)
	{
		if (dp->d_type != DT_DIR && !ft_strncmp(exec, dp->d_name, len))
		{
			exec_path = ft_strjoin_path(path, exec);
			if (stat(exec_path, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
				return (free_path_search(exec_path, dir));
		}
		dp = readdir(dir);
	}
	return (free_path_search(NULL, dir));
}

char	*get_exec_path(char *exec, char *PATH)
{
	char	**paths;
	int		i;
	char	*exec_path;

	paths = ft_split(PATH, ':');
	i = -1;
	exec_path = NULL;
	while (paths[++i] && exec_path == NULL)
		exec_path = search_path(paths[i], exec);
	free_list(paths, 0);
	return (exec_path);
}
