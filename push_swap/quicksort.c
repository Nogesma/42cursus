#include "median.h"
#include <libft.h>
#include "quicksort.h"

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
	while (++i < n && lst && lst->next)
	{
		if (lst->content > lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}
void	quicksort_b(t_list **head_a, t_list **head_b, int n);

void	quicksort_a(t_list **head_a, t_list **head_b, int n);

int ft_lstfind(t_list *lst, int n)
{
	int i;

	if (!lst)
		return (-1);
	i = 0;
	while (lst)
	{
		if (lst->content == n)
			return (i);
		i++;
		lst = lst->next;
	}
	return (-1);
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
int get_closest_index(t_list *lst, int *sorted, int start, int end)
{
	int lindex;
	int mindex;
	int lstsize;

	mindex = -1;
	lstsize = ft_lstsize(lst);
	while (start < end)
	{
//		ft_printf("Searching for %d at index %d...\n", sorted[start], start);
		lindex = ft_lstfind(lst, sorted[start]);
//		ft_printf("Found %d at index %d.\n", sorted[start], lindex);
		if (lindex != -1 && (mindex == -1 || min(mindex, lstsize - mindex) > min(lindex, lstsize - lindex)))
			mindex = lindex;
		start++;
	}
//	ft_printf("Final index: %d\n", mindex);
	return (mindex);
}

void put_stack(t_list **head_a, t_list **head_b, int lindex, int lstsize)
{
	if (lindex <= lstsize / 2)
	{
		while (lindex > 0)
		{
			ft_printf("ra\n");
			rotate_stack(head_a);
			lindex--;
		}
	}
	else
	{
		while (lindex != lstsize)
		{
			ft_printf("rra\n");
			rotate_reverse_stack(head_a);
			lindex++;
		}
	}
	ft_printf("pb\n");
	push_stack(head_a, head_b);
}

int get_interval(t_list *lst, int n, int *split, int *sorted)
{
	int i;
	int minindex;

	i = 0;
	minindex = -1;
	while (minindex == -1)
		minindex = ft_lstfind(lst, sorted[i++]);
	i--;
	if (i + *split > n)
		*split = n - i;
	return (i);
}

void split(t_list **head_a, t_list **head_b)
{
	int n;
	int div = 4;
	int i;
	int j;
	int k;
	int u;
	int lindex;
	int lstsize;
	int *sorted;

	n = ft_lstsize(*head_a);
	int split = n / div;
	sorted = get_sorted(*head_a, n);
	i = -1;
	while (++i <= div)
	{
		j = -1;
		while (++j < n / div)
		{
			lstsize = ft_lstsize(*head_a);
			if (lstsize < 1)
				break;
			k = get_interval(*head_a, n, &split, sorted);
//			ft_printf("%d-%d-%d (%d) (%d) --> %d\n", k, k + split / 2, k + split, ft_lstsize(*head_a), ft_lstsize(*head_b), n);
			lindex = get_closest_index(*head_a, sorted, k, k + split / 2);
			u = get_closest_index(*head_a, sorted, k + split / 2, k + split);
//			ft_printf("(%d) (%d)\n", lindex, u);
			if (u != -1 && (lindex == -1 || min(lindex, lstsize - lindex) > min(u, lstsize - u)))
			{
				put_stack(head_a, head_b, u, lstsize);
				ft_printf("rb\n");
				rotate_stack(head_b);
			}
			else
			{
				put_stack(head_a, head_b, lindex, lstsize);
			}
		}
//			ft_printf("Printing stack a:\n");
//			print_stack(*head_a);
//			ft_printf("\n\n");
//			ft_printf("Printing stack b:\n");
//			print_stack(*head_b);
//			ft_printf("\n\n");
	}
}


void	solve(t_list **head_a, t_list **head_b)
{
	int n;
	int i;
	int *sorted;

//	ft_printf("Starting solve...\n");
	n = ft_lstsize(*head_b) - 1;
	sorted = get_sorted(*head_b, n + 1);
	while (n != -1)
	{
		i = ft_lstfind(*head_b, sorted[n]);
//		ft_printf("Found max: %d, i: %d, n: %d\n", sorted[n], i, n);
		if (i <= n / 2)
		{
			while (i != 0)
			{
				ft_printf("rb\n");
				rotate_stack(head_b);
				i--;
			}
		}
		else
		{
			while (i != n + 1)
			{
				ft_printf("rrb\n");
				rotate_reverse_stack(head_b);
				i++;
			}
		}
		ft_printf("pa\n");
		push_stack(head_b, head_a);
		n--;
	}
}

void clone_lst(t_list *lst, t_list **clone);

int lstmin(t_list *lst)
{
	int i;
	int j;
	int min;

	i = 0;
	j = 0;

	min = lst->content;
	while (lst)
	{
		if (lst->content < min)
		{
			min = lst->content;
			j = i;
		}
		i++;
		lst = lst->next;
	}
	return (j);
}

int lstmax(t_list *lst)
{
	int i;
	int j;
	int max;
	i = 0;
	j = 0;
	max = lst->content;
	while (lst)
	{
		if (lst->content > max)
		{
			max = lst->content;
			j = i;
		}
		i++;
		lst = lst->next;
	}
	return (j);
}

void brute_force3(t_list *lst)
{
	if (lstmin(lst) == 0)
	{
		ft_printf("sa\n");
		ft_printf("ra\n");
	}
	else if (lstmin(lst) == 1)
	{
		if (lstmax(lst) == 0)
			ft_printf("ra\n");
		else
			ft_printf("sa\n");
	}
	else
	{
		if (lstmax(lst) == 1)
			ft_printf("rra\n");
		else
		{
			ft_printf("sa\n");
			ft_printf("rra\n");
		}
	}
}

int sort(t_list **head_a, t_list **head_b, int n)
{
	if (is_sorted(*head_a, n))
		return (1);
	if (n <= 3)
	{
		brute_force3(*head_a);
	}
	if (n <= 5)
	{}
	else
	{
		split(head_a, head_b);
		solve(head_a, head_b);
	}
	return (1);
}


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
		if (is_sorted(*head_a, ft_lstsize(*head_a)))
			break;
//		ft_printf("%p %d, n: %p\n", stack_a, stack_a->content, stack_a->next);
		if (elem->content < pivotValue)
		{
				if (*head_b && elem->content > (*head_b)->content)
				{
					ft_printf("rb\n");
					rotate_stack(head_b);
				}
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
//	ft_printf("\nn: %d\n\n", n);
//	print_stack(*head_b);
	if (ft_lstsize(*head_a) !=  j)
	{
	print_stack(*head_a);
	ft_printf("\nn: %d\n\n", n);
		ft_printf("%d %d\n", ft_lstsize(*head_a), j);
		exit(2);
	}
	if (!is_sorted(*head_a, j))
		quicksort_a(head_a, head_b, j);
//	if (!is_sorted(*head_b, n - j))
//		quicksort_b(head_a, head_b, n - j);
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