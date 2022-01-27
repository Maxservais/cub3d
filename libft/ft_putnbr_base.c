
#include "libft.h"

void	ft_putnbr_base(unsigned long long int nbr, char *base)
{
	unsigned long long int	count;
	char					c;

	count = (unsigned long long int) ft_strlen(base);
	if (nbr >= count)
		ft_putnbr_base(nbr / count, base);
	c = base[nbr % count];
	write(1, &c, 1);
}
