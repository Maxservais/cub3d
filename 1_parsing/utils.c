
#include "../cub3d.h"

int	pass_the_f_or_c(char *line, t_list *lstmap, t_param *param)
{
	int i;

	i = 0;
	while (line[i] && line[i] != 'F' && line[i] != 'C')
		i++;
	if (!line[i])
		free_texture(lstmap, param, FILE_ER, 1);
	return (i);
}
