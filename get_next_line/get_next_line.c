#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *dst;
	char		*temp_read;
	int			size;

	if (!dst)
		dst = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	read(fd, &temp_read, BUFFER_SIZE);
	if (!dst[0])
		ft_strlcpy(dst, temp_read, BUFFER_SIZE);
	else
	{
		size = ft_strlen(dst);
		ft_strlcpy(&dst[size], temp_read, )
	}
	c = 0;
	pos->x = 0;
	pos->y = 0;
	while (c != '\n' && read(fd, &c, 1) > 0)
	{
		if (c != map->empty)
		{
			if (c == map->obstacle)
			{
				(*elem)->next = ft_create_elem(pos->x, pos->y);
				*elem = (*elem)->next;
			}
			else if (c != '\n')
				map->is_valid = 0;
		}
		++pos->x;
	}
	map->x = pos->x - 1;
	++pos->y;
	pos->x = 0;
}