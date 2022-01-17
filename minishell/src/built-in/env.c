/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:47:19 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/10 17:47:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

int	env(__attribute__ ((unused)) char **a, t_list **environ)
{
	t_list	*elem;

	elem = *environ;
	while (elem)
	{
		ft_printf(STDOUT_FILENO, "%s\n", elem->content);
		elem = elem->next;
	}
	return (0);
}
