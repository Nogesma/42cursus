/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:56 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/20 14:32:57 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by tkondrac on 19.01.22.
//

#ifndef REDIRECT_PARSE_H
# define REDIRECT_PARSE_H

char	*next_word_redirect(char *line, t_list **env);
int		which_redirect(char *line);

#endif //REDIRECT_PARSE_H
