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

#include "built_ins.h"

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_printf(STDOUT_FILENO, "%s\n", cwd);
	free(cwd);
}
