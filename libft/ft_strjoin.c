
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*conc_str;

	len = ft_strlen_until(s1, 0) + ft_strlen_until(s2, 0);
	conc_str = malloc(sizeof(char) * (len + 1));
	if (!conc_str)
	{
		free(s1);
		return (NULL);
	}
	conc_str[len] = 0;
	i = -1;
	len = ft_strlen_until(s1, 0);
	if (len > 0)
		while (++i < len)
			conc_str[i] = s1[i];
	i = -1;
	if (ft_strlen_until(s2, 0) > 0)
		while (s2[++i])
			conc_str[i + len] = s2[i];
	free(s1);
	return (conc_str);
}
