
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub_str = malloc(sizeof(char const) * (len + 1));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (*(s + start + i) != '\0' && i < len)
	{
		*(sub_str + i) = *(s + start + i);
		i++;
	}
	*(sub_str + i) = '\0';
	return (sub_str);
}
