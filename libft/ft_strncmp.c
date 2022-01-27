
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	while (i < n && *(s1 + i) != '\0' && *(s1 + i) == *(s2 + i))
		i++;
	if (i == n)
		res = 0;
	else
		res = (unsigned char)*(s1 + i) - (unsigned char)*(s2 + i);
	return (res);
}
