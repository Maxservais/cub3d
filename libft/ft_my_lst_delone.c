#include "libft.h"

t_list	*ft_my_lst_delone(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!(tmp->before) && !(tmp->next))
	{
		free(lst->line);
		free(lst);
		return (NULL);
	}
	if (tmp->before)
	{
		tmp = lst->before;
		tmp->next = lst->next;
	}
	if (tmp->next != NULL)
	{
		tmp = lst->next;
		tmp->before = lst->before;
	}
	free(lst->line);
	free(lst);
	return (tmp);
}
