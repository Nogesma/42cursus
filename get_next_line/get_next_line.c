#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*dst;
	char			*sdst;
	char			*tdst;
	int				newline;

	if (!buffer)
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	dst = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy(dst, buffer);
	newline = ft_strchr(dst, '\n');
	if (newline != -1)
	{
		ft_strcpy(buffer, &dst[newline + 1]);
		dst[newline + 1] = 0;
		return (dst);
	}
//	printf("d:%s\n", buffer);
//	printf("d:%s\n", dst);
	while (newline == -1)
	{
		tdst = dst;
//		printf("t:%s\ns:%s\n", tdst, sdst);

		sdst = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!sdst)
			return (NULL);
		newline = read(fd, sdst, BUFFER_SIZE);
//		printf("ddd:%d\n", dst[0]);
//		printf("ddd:%d\n", sdst[0]);
		dst = ft_strjoin(tdst, sdst);
//		printf("dd:%s\n", dst);
//		printf("dd:%s\n", sdst);
		free(tdst);
		free(sdst);
//		printf("nl:%d\n", newline);
		if (newline < 1)
		{
			if (buffer[0] == 0)
			{
				free(buffer);
				return (NULL);
			}
			newline = ft_strchr(dst, 0);
			buffer[0] = 0;
			dst[newline + 1] = 0;
			return (dst);
		}
		else
			newline = ft_strchr(dst, '\n');
//		printf("nl:%d\n", newline);
//		printf("%s\n", dst);
//		printf("is there a newline? %zu\n", ft_strlen(newline));
	}
//	printf("%d", newline);
	ft_strcpy(buffer, &dst[newline + 1]);
//	printf("d:%d,%d\n", buffer[0], buffer[1]);
	dst[newline + 1] = 0;
//	printf("d:%d,%d\n", dst[0], dst[1]);
//	printf("d:%s\n", dst);
	return (dst);
}

#include <fcntl.h>

int main(int argc, char **argv)
{
	char *line;
	argc = 1;
	int fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("%d | %s", argc++, line);
	while (line)
	{
		line = get_next_line(fd);
		printf("%d | %d", argc++, line == NULL);
	}
}