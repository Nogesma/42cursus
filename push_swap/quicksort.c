#include "median.h"
#include "libft/libft.h"

void print_stack(t_list *lst)
{
	while (lst)
	{
		ft_printf("%d\n", lst->content);
		lst = lst->next;
	}
}

void rotate_stack(t_list **stack)
{
	t_list *temp;

	ft_lstlast(*stack)->next = *stack;
	temp = (*stack)->next;
	(*stack)->next = NULL;
	*stack = temp;
}

void push_stack(t_list **head_a, t_list **head_b)
{
	t_list *temp;

	temp = *head_a;
	*head_a = temp->next;
	temp->next = *head_b;
	*head_b = temp;
}

int is_sorted(t_list *lst, int n)
{
	int i;

	i = -1;
	while (++i < n && lst && lst->next)
	{
		if (lst->content > lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}
void	quicksort(t_list **head_a, t_list **head_b, int n, int s)
{
	int pivotValue;
	t_list *elem;
	int i;

	elem = *head_a;
	pivotValue = get_median_value(*head_a, n);
	i = -1;
	while (++i <= n && elem)
	{
//		ft_printf("%p %d, n: %p\n", stack_a, stack_a->content, stack_a->next);
		if (elem->content < pivotValue)
		{
			if (s)
				ft_printf("pa\n");
			else
				ft_printf("pb\n");
			elem = elem->next;
			push_stack(head_a, head_b);
		}
		else
		{
			if (s)
				ft_printf("ra\n");
			else
				ft_printf("rb\n");
			elem = elem->next;
			rotate_stack(head_a);
		}
	}
//	ft_printf("\npivotValue: %d\n\n", pivotValue);
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	if (n % 2)
		i = n / 2 + 1;
	else
		i = n / 2;
	if (!is_sorted(*head_a, n / 2))
		quicksort(head_a, head_b, n / 2, 0);

	if (!is_sorted(*head_b, i))
		quicksort(head_b, head_a, i, 1);
	elem = *head_b;
	i = -1;
	while (elem && ++i < n)
	{
		ft_printf("pa\n");
		elem = elem->next;
		push_stack(head_b, head_a);
	}
}
