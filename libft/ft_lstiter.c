
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst != NULL && f != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
