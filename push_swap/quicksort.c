#include "median.h"
#include "bubble_sort.h"
#include "libft/libft.h"

void	quicksort(int *list, int left, int right)
{
	int pivotValue;
	t_list *stack;
	int i;
	int j;

	int pivotIndex = get_median_index(&list[left], right - left);
	pivotValue = list[left + pivotIndex];
	i = left;
	j = right;
	while (i <= j)
	{
		while (list[i] < pivotValue)
		{
			ft_printf("ra\n");
			i++;
		}
		while (list[j] > pivotValue)
			j--;
		if (i <= j)
		{
			ft_printf("pb\n");
			ft_printf("ra\n");
			ft_swap(&list[i++], &list[j--]);
		}
	}

//	if (left < j)
//		quicksort(list, left, j);
//	if (i < right)
//		quicksort(list, i, right);
//	i = -1;
//	while (++i < (right - left) / 2)
//		ft_printf("pa\n");
}
