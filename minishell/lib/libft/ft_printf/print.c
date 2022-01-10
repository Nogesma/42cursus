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

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft.h"

int	print_s(va_list args, int fd)
{
	char	*s;

	s = va_arg(args, char *);
	if (s == NULL)
		return (write(fd, "(null)", 6));
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

int	print_d(va_list args, int fd)
{
	int		n;
	char	*a;

	n = va_arg(args, int);
	a = ft_itoa(n);
	ft_putstr_fd(a, fd);
	n = ft_strlen(a);
	free(a);
	return (n);
}

int	print_base(unsigned long n, char *base, int fd)
{
	unsigned long	bl;
	int				i;

	bl = ft_strlen(base);
	i = 1;
	if (n < bl)
		ft_putchar_fd(base[n], fd);
	else
	{
		i = 1 + print_base(n / bl, base, fd);
		ft_putchar_fd(base[n % bl], fd);
	}
	return (i);
}

int	print_p(va_list args, int fd)
{
	unsigned long	p;

	p = va_arg(args, unsigned long);
	if (!p)
		return (write(fd, "(nil)", 5));
	ft_putstr_fd("0x", fd);
	return (print_base(p, "0123456789abcdef", fd) + 2);
}
