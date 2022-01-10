#include <libft.h>

int	env(t_list *environ)
{
	while (environ)
	{
		ft_printf(1, "%s\n", environ->content);
		environ = environ->next;
	}
	return (0);
}
