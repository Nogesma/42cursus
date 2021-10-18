#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

int		ft_strcpy(char *dest, const char *src);

size_t	ft_strlen(const char *s);

int		ft_strchr(const char *s, int c);

char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_calloc(size_t count, size_t size);

char	*get_next_line(int fd);

#endif //GET_NEXT_LINE_H
