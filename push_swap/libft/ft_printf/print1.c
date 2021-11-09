/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:59:50 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/20 15:00:12 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_c(va_list args)
{
	char	c;

	c = va_arg(args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_s(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	print_d(va_list args)
{
	int		n;
	char	*a;

	n = va_arg(args, int);
	a = ft_itoa(n);
	ft_putstr_fd(a, 1);
	n = ft_strlen(a);
	free(a);
	return (n);
}

static int	print_base_long(unsigned long n, char *base)
{
	unsigned long	bl;
	int				i;

	bl = ft_strlen(base);
	i = 1;
	if (n < bl)
		ft_putchar_fd(base[n], 1);
	else
	{
		i = 1 + print_base_long(n / bl, base);
		ft_putchar_fd(base[n % bl], 1);
	}
	return (i);
}

int	print_p(va_list args)
{
	unsigned long	p;

	p = va_arg(args, unsigned long);
	ft_putstr_fd("0x", 1);
	return (print_base_long(p, "0123456789abcdef") + 2);
}
