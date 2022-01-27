
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;
	unsigned char	my_c;

	i = 0;
	ptr_s = (unsigned char *)s;
	my_c = (unsigned char)c;
	while (i < n)
	{
		if (*(ptr_s + i) == my_c)
		{
			return (ptr_s + i);
		}
		i++;
	}
	return (NULL);
}
