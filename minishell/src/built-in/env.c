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

int	env(t_list *environ)
{
	while (environ)
	{
		ft_printf(1, "%s\n", environ->content);
		environ = environ->next;
	}
	return (0);
}
