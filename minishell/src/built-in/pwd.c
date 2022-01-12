/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:07:02 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/27 15:07:04 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	pwd(__attribute__ ((unused)) char **a, __attribute__ ((unused)) t_list **_)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	free(cwd);
	return (0);
}
