
#include "get_next_line.h"

int	is_in_str(char *str, char c)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

char	*ft_strdup_from(char *str, int from)
{
	int		i;
	char	*dest;

	if (!str)
		return (NULL);
	if (!is_in_str(str, '\n'))
	{
		free(str);
		return (NULL);
	}
	i = ft_strlen_until(str + from, 0);
	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	dest[i] = 0;
	i = -1;
	while (str[++i + from])
		dest[i] = str[i + from];
	free(str);
	return (dest);
}
