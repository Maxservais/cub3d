
#include "libft.h"

static int	ft_overflow(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((*(nptr + i) >= 9 && *(nptr + i) <= 13) || *(nptr + i) == 32)
		i++;
	if (*(nptr + i) == ' ' || *(nptr + i) == '-' || *(nptr + i) == '+')
	{
		if (*(nptr + i) == '-')
			sign = -1;
		i++;
	}
	while (*(nptr + i) != '\0' && ft_isdigit(*(nptr + i)))
	{
		if (res > LONG_MAX / 10)
			return (ft_overflow(sign));
		res = (10 * res) + (*(nptr + i) - '0');
		if (res < 0)
			return (ft_overflow(sign));
		i++;
	}
	return (sign * res);
}
