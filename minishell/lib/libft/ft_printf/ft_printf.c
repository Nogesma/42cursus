/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:56:59 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/19 17:57:08 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "../libft.h"

int	print_special(char c, int fd, va_list args)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		return (1);
	}
	if (c == 's')
		return (print_s(args, fd));
	if (c == 'p')
		return (print_p(args, fd));
	if (c == 'd' || c == 'i')
		return (print_d(args, fd));
	if (c == 'u')
		return (print_base(va_arg(args, unsigned int), "0123456789", fd));
	if (c == 'x')
		return (print_base(va_arg(args, unsigned int), "0123456789abcdef", fd));
	if (c == 'X')
		return (print_base(va_arg(args, unsigned int), "0123456789ABCDEF", fd));
	if (c == '%')
		return (write(fd, "%", 1));
	return (-1);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		to;
	int		sum;
	int		from;
	int		t;
	va_list	args;

	to = -1;
	from = 0;
	sum = 0;
	va_start(args, str);
	while (str[++to])
	{
		if (str[to] == '%')
		{
			write(fd, str + from, to - from);
			t = print_special(str[to + 1], fd, args);
			if (t == -1)
				return (to + sum);
			sum = sum + t - 2;
			from = ++to + 1;
		}
	}
	va_end(args);
	write(fd, str + from, to - from);
	return (to + sum);
}
