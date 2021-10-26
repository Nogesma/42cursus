/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:01:24 by msegrans          #+#    #+#             */
/*   Updated: 2021/10/22 17:01:27 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

int		ft_strcpy(char *dest, const char *src);

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char *s1, char *s2);

void	*ft_calloc(size_t count, size_t size);

void	ft_bzero(void *s, size_t n);

char	*get_next_line(int fd);

#endif //GET_NEXT_LINE_BONUS_H
