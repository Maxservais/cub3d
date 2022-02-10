#include "libft.h"

static char	*copy_the_char(char *str, int len, int j)
{
	char	*nw;
	int		i;

	nw = malloc(sizeof (char) * (len + 1));
	if (!nw)
		return (NULL);
	i = -1;
	while (++i < len)
		nw[i] = str[j++];
	nw[i] = '\0';
	return (nw);
}

char	*ft_my_strlcpy(char *str)
{
	int		i;
	int		len;
	char	*nw;
	int		j;

	i = 0;
	len = 0;
	while (str[i] && ft_is_wspace(str[i]))
		i++;
	i += 2;
	while (str[i] && ft_is_wspace(str[i]))
		i++;
	j = i;
	while (str[i] && !(ft_is_wspace(str[i])))
	{
		i++;
		len++;
	}
	if (ft_str_iswspace(&(str[i])))
		return (NULL);
	nw = copy_the_char(str, len, j);
	if (!nw)
		return (NULL);
	return (nw);
}
