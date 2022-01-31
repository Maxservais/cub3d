#include "libft.h"

char	*ft_my_strlcpy(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_wspace(str[i]))
		i++;
	if (!str[i])
		return (NULL);

}

//je voudrais faire une copy jusqu'au prochaine wspace et le renvoyer.
