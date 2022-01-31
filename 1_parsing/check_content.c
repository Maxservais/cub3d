
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

void	get_the_texture(char *line, t_map *map, int identifier, int *ret)
{
	while (str[i] && ft_is_wspace(str[i]))
		i++;
	if (str[i])
		ft_error(FILE_ERROR);
	if (identifier == 1)
		map->NO_texture = ft_my_strlcpy(&(str[i]));
	*ret++;
}

//ici la fonction va recevoir une string copie de la texture sans les esapces. 

int	find_the_element(t_map *map, char *line, int ret)
{
	if (ft_my_strncmp(line, "NO", 2) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 1, &ret);
	else if (ft_my_strncmp(line, "SO", 2) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 2, &ret);
	else if (ft_my_strncmp(line, "EA", 2) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 3, &ret);
	else if (ft_my_strncmp(line, "WE", 2) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 4, &ret);
	/*else if (ft_my_strncmp(line, "F", 1) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 5, &ret);
	else if (ft_my_strncmp(line, "C", 1) == 0 && !(map->NO_texture)) il faut que je lasse pour les couleurs
		get_the_texture(line, map, 6, &ret);*/
	else if (ret != 6)
		ft_error(FILE_ERROR);
	return (ret);
}

/*
the fonction check_content retrieves the e texture path for each element.
*/
int	check_content(t_map *map, t_list *lstmap)
{
	int		ret;

	ret = 0;
	while (lstmap && ret < 6)
	{
		ret = find_the_element(map, lstmap->line, ret);
		lstmap = lstmap->next;
	}
	return (1);
}
