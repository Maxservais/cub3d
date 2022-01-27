
#include "libft.h"

int	ft_long_len(unsigned long int nbr, char *base)
{
	int	len;
	int	i;

	len = ft_strlen(base);
	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / len;
		i++;
	}
	return (i);
}
