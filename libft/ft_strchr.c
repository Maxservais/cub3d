
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	my_c;

	i = 0;
	str = (char *)s;
	my_c = (unsigned char)c;
	while (*(str + i) != my_c)
	{
		if (*(str + i) == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return (str + i);
}
