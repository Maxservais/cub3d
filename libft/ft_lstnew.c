
#include "libft.h"

t_list	*ft_lstnew(void *line)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	(*node).line = line;
	(*node).next = NULL;
	(*node).before = NULL;
	return (node);
}
