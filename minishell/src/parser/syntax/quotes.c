/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 02:22:37 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/18 02:22:39 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "../../utils/error.h"

int	check_quotes(char *line)
{
	char	single_quote;
	char	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			++single_quote;
		if (*line == '"')
			++double_quote;
		++line;
	}
	if (single_quote % 2)
		return (syntax_error("'"));
	if (double_quote % 2)
		return (syntax_error("\""));
	return (0);
}
