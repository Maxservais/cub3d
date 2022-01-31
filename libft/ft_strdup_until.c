
#include "libft.h"

char	*ft_strdup_until(char *src, char c)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	i = ft_strlen_until(src, c);
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
	{
		free(src);
		return (NULL);
	}
	dest[i] = 0;
	i = -1;
	while (src[++i] && src[i] != c)
		dest[i] = src[i];
	return (dest);
}
