#include "libft.h"

t_list	*ft_my_lst_delone(t_list *lst)
{
	t_list *tmp;

	tmp = lst->next;
	free(lst->line);
	free(lst);
	return (tmp);
}
