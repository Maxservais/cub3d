
#include "../cub3d.h"

/*
- Each element (except the map) first's information is the type identifier
(composed by one or two character(s)), followed by all specific informations for each object in a strict order
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any
order in the file.
- Except for the map, each type of information from an element can be separated by one or more space(s).
*/

// int	check_elements(t_param *param, char *filename)
// {
// 	return (0);
// }

/*
	Cette fonction va comparer a partir de la string envoyer si les characteres correspondent a des identifieurs.
	Si c'est bon il enregistrera l'informations dans la struct map aussi non il renverra une erreur.
*/
void	identifier_element(t_map *map, char *line, int i)
{
	if (ft_strncmp(line, "NO ", 3) != 0)
		ft_error(ELEMENT_ER);
	else
		map->NO_texture = line;
	printf("%d\n", i);
}


/*
the fonction check_content retrieves the e texture path for each element.
*/
int	check_content(t_map *map, t_list *lstmap)
{
	t_list	*tmp;
	int		i;

	tmp = lstmap;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i])
		{
			if (ft_is_wspace(tmp->line[i]))
				i++;
			else
			{
				identifier_element(map, &(tmp->line[i]), i);
				break;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
