
#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned long int		nbr;
	char					c;

	nbr = n;
	if (n < 0)
		nbr *= -1;
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	c = nbr % 10 + '0';
	write(1, &c, 1);
}
