
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

void	get_the_texture(char *line, t_map *map, int identifier)
{
	if (identifier == 1)
	{
		map->NO_texture = ft_my_strlcpy(line);
		if (!map->NO_texture)
			ft_error(MALLOC_ER);
	}
	else if (identifier == 2)
	{
		map->SO_texture = ft_my_strlcpy(line);
		if (!map->SO_texture)
			ft_error(MALLOC_ER);
	}
	else if (identifier == 3)
	{
		map->EA_texture = ft_my_strlcpy(line);
		if (!map->EA_texture)
			ft_error(MALLOC_ER);
	}else if (identifier == 4)
	{
		map->WE_texture = ft_my_strlcpy(line);
		if (!map->WE_texture)
			ft_error(MALLOC_ER);
	}
}

void	get_the_color(char *line, t_map *map, int identifier)
{
//creer la gestion pour recuperer les couleurs !
}

int	find_the_element(t_map *map, char *line)
{
	write(1, "je suis l2\n", 11);
	if (ft_my_strncmp(line, "NO", 2) == 0 && !(map->NO_texture))
	{
		get_the_texture(line, map, 1);
		write(1, "je suis l3\n", 11);
	}
	else if (ft_my_strncmp(line, "SO", 2) == 0 && !(map->SO_texture))
	{
		write(1, "je suis l4\n", 11);
		get_the_texture(line, map, 2);
	}
	else if (ft_my_strncmp(line, "EA", 2) == 0 && !(map->EA_texture))
	{
		get_the_texture(line, map, 3);
		write(1, "je suis l5\n", 11);
	}
	else if (ft_my_strncmp(line, "WE", 2) == 0 && !(map->WE_texture))
	{
		get_the_texture(line, map, 4);
		write(1, "je suis l6\n", 11);
	}
	else if (ft_my_strncmp(line, "F", 1) == 0 && !(map->Floor_color))
	{
		get_the_color(line, map, 1);
	}
	else if (ft_my_strncmp(line, "C", 1) == 0 && !(map->ceilling_color))
		;
	else
		return (0);
	return (1);
}

/*
the fonction check_content retrieves the e texture path for each element.
*/
int	check_content(t_map *map, t_list *lstmap)
{
	int		ret;

	ret = 0;
	write(1, "je suis la\n", 11);
	while (lstmap && ret < 4)//changer en 6 quand sol et ciel
	{
		write(1, "je suis l1\n", 11);
		ret += find_the_element(map, lstmap->line);
		printf("ret == %d\n", ret);
		lstmap = lstmap->next;
	}
	printf("NO == |%s|\nSO == |%s|\nEA == |%s|\nWE == |%s|\n", map->NO_texture, map->SO_texture, map->EA_texture, map->WE_texture);
	exit(EXIT_FAILURE);
	return (1);
}
