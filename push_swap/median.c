#include "bubble_sort.h"
#include <stdlib.h>

static int *clone_list(const int *src, int n)
{
	int *dest;
	int i;

	dest = (int *)malloc((n) * sizeof(int));
	i = -1;
	while (++i < n)
		dest[i] = src[i];
	return (dest);
}

static int get_index(const int *list, int n, int median)
{
	int i;

	i = -1;
	while (++i < n)
		if (list[i] == median)
			return (i);
	return (-1);
}

int get_median_index(int *list, int n)
{
	int *sort;
	int i;

	if (n < 3)
		return (0);
	sort = clone_list(list, n);
	bubble_sort(sort, n);
	i = get_index(list, n, sort[n / 2]);
	free(sort);
	return (i);
}