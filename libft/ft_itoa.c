
#include "libft.h"

static int	ft_sizeofint(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				len;
	int				sign;
	unsigned long	nbr;
	char			*str;

	nbr = n;
	len = ft_sizeofint(n);
	sign = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nbr *= -1;
		sign = 1;
	}
	str[len] = '\0';
	while (len-- > sign)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}
