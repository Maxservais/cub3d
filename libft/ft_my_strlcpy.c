#include "libft.h"

char	*ft_my_strlcpy(char *str)
{
	int		i;
	int		len;
	int		j;
	char	*nw;

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
	nw = malloc(sizeof (char) * (len + 1));
	if (!nw)
		return (NULL);
	i = -1;
	while (++i < len)
		nw[i] = str[j++];
	nw[i] = '\0';
	return (nw);
}

//je voudrais faire une copy jusqu'au prochaine wspace et le renvoyer.
