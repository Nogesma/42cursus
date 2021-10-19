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
	ft_strcpy(dst, buffer);
	buffer[0] = 0;
	newline = ft_strchr(dst, '\n');
	if (newline != -1)
	{
		ft_strcpy(buffer, &dst[newline + 1]);
		dst[newline + 1] = 0;
		sdst = (char *)ft_calloc(newline + 1, sizeof(char));
		if (!sdst)
			return (NULL);
		ft_strcpy(sdst, dst);
		free(dst);
		printf("a:%s\n", sdst);
		return (sdst);
	}
	while (newline == -1)
	{
		tdst = dst;
		sdst = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!sdst)
			return (NULL);
		newline = (int)read(fd, sdst, BUFFER_SIZE);
		dst = ft_strjoin(tdst, sdst);
		if (newline < 1)
		{
			buffer [0] = 0;
			if (dst[0])
			{
				printf("b:%s\n", dst);
				return (dst);
			}
			free(dst);
			return (NULL);
		}
		else if (newline < BUFFER_SIZE)
		{
			newline = ft_strchr(dst, '\n');
			if (newline == -1)
				newline = ft_strchr(dst, 0);
		}
		else
			newline = ft_strchr(dst, '\n');
	}
	if (newline != (int)ft_strlen(dst))
		ft_strcpy(buffer, &dst[newline + 1]);
	dst[newline + 1] = 0;
	sdst = (char *)ft_calloc(newline + 1, sizeof(char));
	if (!sdst)
		return (NULL);
	ft_strcpy(sdst, dst);
	free(dst);
	printf("c:%s\n", sdst);
	return (sdst);
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
