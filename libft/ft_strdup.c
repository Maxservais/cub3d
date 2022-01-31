
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		len;

	len = ft_strlen(s);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, len + 1);
	return (dst);
}
