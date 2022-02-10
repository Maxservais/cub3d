#include "libft.h"

int	ft_is_a_map(char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_is_wspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || ft_is_wspace(line[i])
			|| line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
			|| line[i] == 'W')
			i++;
		else
			return (1);
	}
	return (0);
}
