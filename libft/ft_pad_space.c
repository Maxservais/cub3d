
#include "libft.h"
#include "../include/printf.h"

int	ft_pad_space(int size, int limit)
{
	int	i;

	i = 0;
	while (size < limit)
	{
		ft_putchar(' ');
		size++;
		i++;
	}
	return (i);
}
