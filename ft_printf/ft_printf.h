/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:53:17 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/20 14:53:19 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

int	print_c(va_list args);

int	print_s(va_list args);

int	print_d(va_list args);

int	print_p(va_list args);

int	print_x(va_list args);

int	print_bigx(va_list args);

int	print_u(va_list args);

int	ft_printf(const char *str, ...);

#endif //FT_PRINTF_H
