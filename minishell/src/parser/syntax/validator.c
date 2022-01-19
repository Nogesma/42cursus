/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:29:36 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/17 21:29:37 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "braces.h"
#include "pipes.h"
#include "quotes.h"
#include "op.h"
#include "redirection.h"

int	check_line(char *line)
{
	return (check_quotes(line) || check_double(line, "&&")
		|| check_double(line, "||") || check_pipes(line)
		|| check_redir(line, ">>") || check_redir(line, "<<")
		|| check_redir(line, "<") || check_redir(line, ">")
		|| check_braces(line, line));
}
