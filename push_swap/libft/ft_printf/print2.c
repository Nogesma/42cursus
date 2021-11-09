/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:00:20 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/20 15:00:22 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_base(unsigned int n, char *base)
{
	unsigned int	bl;
	int				i;

	bl = ft_strlen(base);
	i = 1;
	if (n < bl)
		ft_putchar_fd(base[n], 1);
	else
	{
		i = 1 + print_base(n / bl, base);
		ft_putchar_fd(base[n % bl], 1);
	}
	return (i);
}

int	print_x(va_list args)
{
	unsigned int	x;

	x = va_arg(args, unsigned int);
	return (print_base(x, "0123456789abcdef"));
}

int	print_bigx(va_list args)
{
	unsigned int	bigx;

	bigx = va_arg(args, unsigned int);
	return (print_base(bigx, "0123456789ABCDEF"));
}

int	print_u(va_list args)
{
	unsigned int	u;

	u = va_arg(args, unsigned int);
	return (print_base(u, "0123456789"));
}
