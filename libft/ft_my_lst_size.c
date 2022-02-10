#include "libft.h"

int	ft_my_lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && ft_is_a_map(lst->line))
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
