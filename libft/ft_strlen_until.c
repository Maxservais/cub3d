
#include "libft.h"

size_t	ft_strlen_until(char *str, char c)
{
	size_t	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i] && str[i] != c)
		;
	return (i);
}
