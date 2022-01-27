
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		len_needle;

	i = 0;
	len_needle = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*(haystack + i) != '\0' && len_needle <= len)
	{
		if (ft_memcmp(haystack + i, needle, len_needle) == 0)
			return ((char *)haystack + i);
		i++;
		len--;
	}
	return (0);
}
