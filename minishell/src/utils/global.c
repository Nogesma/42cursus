/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 05:31:27 by msegrans          #+#    #+#             */
/*   Updated: 2021/12/31 05:31:30 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	status_code(unsigned char set, unsigned char n)
{
	static unsigned char	status;

	if (set)
		status = n;
	return (status);
}

unsigned char	is_fork(unsigned char set, unsigned char n)
{
	static unsigned char	is_fork;

	if (set)
		is_fork = n;
	return (is_fork);
}
