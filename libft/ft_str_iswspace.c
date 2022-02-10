#include "libft.h"
#include <stdio.h>

int	ft_str_iswspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || (line[i] == ' '))
			i++;
		else
			return (1);
	}
	return (0);
}
