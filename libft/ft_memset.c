
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	my_c;
	unsigned char	*ptr;

	i = 0;
	my_c = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		*(ptr + i) = my_c;
		i++;
	}
	return (s);
}
