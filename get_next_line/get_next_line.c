#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	char			*dst;
	char			*sdst;
	char			*tdst;
	int				newline;

	dst = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!dst)
		return (NULL);
	newline = ft_strchr(dst, '\n');
	if (newline != -1)
	{
		ft_strcpy(buffer, &dst[newline + 1]);
		dst[newline + 1] = 0;
		return (dst);
	}
	while (newline == -1)
	{
		tdst = dst;
		sdst = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!sdst)
			return (NULL);
		newline = read(fd, sdst, BUFFER_SIZE);
		dst = ft_strjoin(tdst, sdst);
		if (newline < 1)
		{
			if (dst[0])
				return (dst);
			free(dst);
			newline = BUFFER_SIZE + 1;
			while (newline --> 0)
				buffer[newline] = 0;
			return (NULL);
		}
		else if (newline < BUFFER_SIZE)
			newline = ft_strchr(dst, 0);
		else
			newline = ft_strchr(dst, '\n');
	}
	ft_strcpy(buffer, &dst[newline + 1]);
	dst[newline + 1] = 0;
	return (dst);
}

#include <fcntl.h>

//int main(int argc, char **argv)
//{
//	char *line;
//	argc = 1;
//	int fd = open(argv[1], O_RDWR);
//	line = get_next_line(fd);
////	printf("%d | %s", argc++, line);
//	while (line)
//	{
//		printf("%d | %s", argc++, line);
//		line = get_next_line(fd);
//	}
//	close(fd);
//}