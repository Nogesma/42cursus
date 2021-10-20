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

#include "ft_printf.h"

int	print_special(char c, va_list args)
{
	if (c == 'c')
		return (print_c(args));
	if (c == 's')
		return (print_s(args));
	if (c == 'p')
		return (print_p(args));
	if (c == 'd' || c == 'i')
		return (print_d(args));
	if (c == 'u')
		return (print_u(args));
	if (c == 'x')
		return (print_x(args));
	if (c == 'X')
		return (print_bigx(args));
	if (c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (-1);
}

int	ft_printf(const char *str, ...)
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
			write(1, &str[from], to - from);
			t = print_special(str[to + 1], args);
			if (t == -1)
				return (to + sum);
			sum = sum + t - 2;
			from = ++to + 1;
		}
	}
	va_end(args);
	write(1, &str[from], to - from);
	return (to + sum);
}
