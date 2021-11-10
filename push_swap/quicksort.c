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

void rotate_reverse_stack(t_list **stack)
{
	t_list *temp;

	temp = *stack;
	if (!temp)
		return ;
	while (temp && temp->next && temp->next->next)
		temp = temp->next;
	temp->next->next = *stack;
	*stack = temp->next;
	temp->next = NULL;
}

void push_stack(t_list **head_a, t_list **head_b)
{
	t_list *temp;

	temp = *head_a;
	if (temp)
	{
		*head_a = temp->next;
		temp->next = *head_b;
		*head_b = temp;
	}
}

int is_sorted(t_list *lst, int n)
{
	int i;

	i = -1;
	while (++i < n - 1 && lst && lst->next)
	{
		if (lst->content > lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}
void	quicksort_b(t_list **head_a, t_list **head_b, int n);

void	quicksort_a(t_list **head_a, t_list **head_b, int n)
{
	int pivotValue;
	t_list *elem;
	int i;
	int j;

	elem = *head_a;
	pivotValue = get_median_value(*head_a, n);
	i = -1;
	j = 0;
	while (++i < n && elem)
	{
//		ft_printf("%p %d, n: %p\n", stack_a, stack_a->content, stack_a->next);
		if (elem->content < pivotValue)
		{
				ft_printf("pb\n");
				elem = elem->next;
				push_stack(head_a, head_b);
		}
		else
		{
			ft_printf("ra\n");
			elem = elem->next;
			rotate_stack(head_a);
			j++;
		}
	}
//	ft_printf("\npivotValue: %d\n\n", pivotValue);
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	if (!is_sorted(*head_a, j))
		quicksort_a(head_a, head_b, j);

	if (!is_sorted(*head_b, n - j))
		quicksort_b(head_a, head_b, n - j);
//	if (s)
//		elem = *head_b;
//	else
//		elem = *head_a;
//	i = -1;
//	while (elem && ++i < n)
//	{
//		ft_printf("pa\n");
//		elem = elem->next;
//		push_stack(head_b, head_a);
//	}
}

void	quicksort_b(t_list **head_a, t_list **head_b, int n)
{
	int pivotValue;
	t_list *elem;
	int i;
	int j;

	elem = *head_b;
	pivotValue = get_median_value(*head_b, n);
	i = -1;
	j = 0;
	while (++i <= n && elem)
	{
//		ft_printf("%p %d, n: %p\n", stack_a, stack_a->content, stack_a->next);
		if (elem->content > pivotValue)
		{
				ft_printf("pa\n");
				elem = elem->next;
				push_stack(head_b, head_a);
		}
		else
		{
			ft_printf("rb\n");
			elem = elem->next;
			rotate_stack(head_b);
			j++;
		}
	}
//	ft_printf("\npivotValue: %d\n\n", pivotValue);
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	i = -1;
	while (++i < j)
	{
		ft_printf("rrb\n");
		rotate_reverse_stack(head_b);

	}
//	if (n % 2)
//		i = n / 2 + 1;
//	else
//		i = n / 2;

	if (!is_sorted(*head_b, j - 1))
		quicksort_b(head_a, head_b, j - 1);

	if (!is_sorted(*head_a, n - j + 1))
		quicksort_a(head_a, head_b, n - j + 1);

//	if (s)
//		elem = *head_b;
//	else
//		elem = *head_a;
//	i = -1;
//	while (elem && ++i < n)
//	{
//		ft_printf("pa\n");
//		elem = elem->next;
//		push_stack(head_b, head_a);
//	}
}