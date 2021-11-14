#include "quicksort.h"

void	print_stack(t_list *lst)
{
	while (lst)
	{
		ft_printf("%d\n", lst->content);
		lst = lst->next;
	}
}

int	is_sorted(t_list *lst, int n)
{
	int	i;

	i = -1;
	while (++i < n && lst && lst->next)
	{
		if (lst->content > lst->next->content)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	ft_lstfind(t_list *lst, int n)
{
	int	i;

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

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	get_closest_index(t_list *lst, int *sorted, int start, int end)
{
	int	lindex;
	int	mindex;
	int	lstsize;

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

void put_stack(t_list **head_a, t_list **head_b, int lindex)
{
	int lstsize;

	lstsize = ft_lstsize(*head_a);
//	ft_printf("ss: %d %d %d\n", lindex, lstsize / 2, lstsize);
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
	int	i;
	int	minindex;

	i = 0;
	minindex = -1;
	while (minindex == -1)
		minindex = ft_lstfind(lst, sorted[i++]);
	i--;
	if (i + *split > n)
		*split = n - i;
	return (i);
}

void split(t_list **head_a, t_list **head_b, int div)
{
	int n;
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
				put_stack(head_a, head_b, u);
				ft_printf("rb\n");
				rotate_stack(head_b);
			}
			else
			{
				put_stack(head_a, head_b, lindex);
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
	int	n;
	int	i;
	int	*sorted;

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

int	lstmin(t_list *lst)
{
	int	i;
	int	j;
	int	min;

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

int	lstmax(t_list *lst)
{
	int	i;
	int	j;
	int	max;

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

void	brute_force3(t_list *lst)
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

void swap_stack(t_list **head_a)
{
	t_list *temp;

	temp = (*head_a)->next;
	(*head_a)->next = temp->next;
	temp->next = *head_a;
	*head_a = temp;

}

void put5(t_list **head_a, t_list **head_b, int lindex)
{
	int lstsize;

	lstsize = ft_lstsize(*head_a);
//	ft_printf("ss: %d %d %d\n", lindex, lstsize / 2, lstsize);
	if (lindex <= (lstsize) / 2)
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
	ft_printf("pa\n");
	push_stack(head_b, head_a);
}

void insert(t_list **head_a, t_list **head_b, int *sorted, int n)
{
	int i;
	int lindex;
	int gindex;

	i = 0;
	while (i < n && sorted[i] != (*head_b)->content)
		i++;
//	ft_printf("ss: %d %d\n", i, sorted[i]);
	if (i != 0)
		lindex = ft_lstfind(*head_a, sorted[i - 1]);
	else
		lindex = ft_lstfind(*head_a, sorted[n - 1]);
	if (i != n - 1)
		gindex = ft_lstfind(*head_a, sorted[i + 1]);
	else
		gindex = ft_lstfind(*head_a, sorted[0]);
//	ft_printf("li: %d gi: %d\n", lindex, gindex);
	if (lindex != -1)
		put5(head_a, head_b, lindex + 1);
	else if (gindex != -1)
		put5(head_a, head_b, gindex);
}

void rollback(t_list **head, int n)
{
	int i;

	i = -1;
	while (++i < n)
		rotate_reverse_stack(head);
}

int iss(t_list **head)
{
	int i;
	int j;
	t_list *lst;

	j = 0;
	while (j < ft_lstsize(*head))
	{
		i = 0;
		lst = *head;
		while (lst && lst->next)
		{
			if (lst->content > lst->next->content)
				break;
			i++;
			lst = lst->next;
		}
		if (!lst->next)
		{
			rollback(head, j);
			return (1);
		}
		j++;
		rotate_stack(head);
	}
	rollback(head, j);
	return (0);
}


void brute_force5(t_list **head_a, t_list **head_b)
{
	int lstsize = ft_lstsize(*head_a);
	int *sorted = get_sorted(*head_a, lstsize);
//	ft_printf("%d\n", iss(*head_a));
	if (!iss(head_a))
	{
		ft_printf("pb\n");
		push_stack(head_a, head_b);
		if (!iss(head_a))
		{
			ft_printf("pb\n");
			push_stack(head_a, head_b);
			if ((lstmin(*head_a) == 0 && lstmax(*head_a) != 2)
				|| (lstmin(*head_a) == 1 && lstmax(*head_a) != 0)
				|| (lstmin(*head_a) == 2 && lstmax(*head_a) != 1))
			{
				ft_printf("sa\n");
				swap_stack(head_a);
			}
		}
	}
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
//	ft_printf("%d %d\n", lstmin(*head_a), lstmax(*head_a));
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	if (ft_lstsize(*head_b) != 0)
		insert(head_a, head_b, sorted, lstsize);
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	if (ft_lstsize(*head_b) != 0)
		insert(head_a, head_b, sorted, lstsize);

//	ft_printf("%d %d %d\n", lstmin(*head_a), ft_lstsize(*head_a) / 2, ft_lstsize(*head_a));
//	print_stack(*head_a);
//	ft_printf("\n");
//	print_stack(*head_b);
//	ft_printf("\n");
	if (lstmin(*head_a) <= ft_lstsize(*head_a) / 2)
	{
		while (lstmin(*head_a) != 0)
		{
			ft_printf("ra\n");
			rotate_stack(head_a);
		}
	}
	else
	{
		while (lstmin(*head_a) != 0)
		{
			ft_printf("rra\n");
			rotate_reverse_stack(head_a);
		}
	}
}

int	ft_sqrt(int nb)
{
	long	i;
	long	p;

	i = 0;
	p = 0;
	while (p <= nb)
	{
		if (p > nb)
			return (i);
		++i;
		p = i * i;
	}
	return (i);
}

void	sort(t_list **head_a, int n)
{
	t_list	**head_b;

	if (is_sorted(*head_a, n))
		return ;
	if (n <= 3)
		return (brute_force3(*head_a));
	head_b = (t_list **)malloc(sizeof(t_list *));
	if (!head_b)
	{
		free(head_b);
		ft_lstclear(head_a);
		free(head_a);
		return ;
	}
	(*head_b) = 0;
	else if (n <= 5)
	{
		brute_force5(head_a, head_b);
	}
	else if (n <= 76)
	{
		split(head_a, head_b, 3);
		solve(head_a, head_b);
	}
	else
	{
		split(head_a, head_b, (int)(ft_sqrt(n) / 2.5));
		solve(head_a, head_b);
//		ft_printf("%d %d %d", n, ft_sqrt(n), (int)(ft_sqrt(n) / 2.5));
	}
	free(head_b);
	ft_lstclear(head_a);
	free(head_a);
}
