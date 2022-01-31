
#include "libft.h"
#include "../include/printf.h"

int	ft_pad_zero(int size, int limit)
{
	int	i;

	i = 0;
	while (size < limit)
	{
		ft_putchar('0');
		size++;
		i++;
	}
	return (i);
}
