#include "get_next_line.h"

int	ft_strcpy(char *dest, const char *src)
{
	int			i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = 0;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	s;
	unsigned char	*m;

	s = count * size;
	m = (unsigned char *)malloc(s);
	if (m == NULL)
		return (NULL);
	while (size-- > 0)
		m[size] = 0;
	return ((void *)m);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1l;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	str = (char *)ft_calloc(s1l + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + s1l, s2);
	return (str);
}
