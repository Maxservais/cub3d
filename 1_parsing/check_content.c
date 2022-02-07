
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
			ft_error(FILE_ERROR);
	}
	else if (identifier == 2)
	{
		map->SO_texture = ft_my_strlcpy(line);
		if (!map->SO_texture)
			ft_error(FILE_ERROR);
	}
	else if (identifier == 3)
	{
		map->EA_texture = ft_my_strlcpy(line);
		if (!map->EA_texture)
			ft_error(FILE_ERROR);
	}else if (identifier == 4)
	{
		map->WE_texture = ft_my_strlcpy(line);
		if (!map->WE_texture)
			ft_error(FILE_ERROR);
	}
}

void	get_the_color(char *line, t_map *map, int identifier)
{
	int		i;
	char	**str;

	while (*line && !(i = ft_isdigit(*line)))
		line++;
	if (!*line)
		ft_error(COLOR_ER);
	i = -1;
	str = ft_split(line, ',');
	if (!str)
		ft_error(MALLOC_ER);
	if (identifier == 1)
	{
		while (++i < 3)
		{
			map->Floor[i] = ft_atoi(str[i]);
			if (map->Floor[i] < 0 || map->Floor[i] > 255)
				ft_error(COLOR_ER);
		}
	}
	if (identifier == 2)
	{
		while (++i < 3)
		{
			map->Ceilling[i] = ft_atoi(str[i]);
			if (map->Ceilling[i] < 0 || map->Ceilling[i] > 255)
				ft_error(COLOR_ER);
		}
	}
}

int	find_the_element(t_map *map, char *line)
{
	if (ft_my_strncmp(line, "NO", 2) == 0 && !(map->NO_texture))
		get_the_texture(line, map, 1);
	else if (ft_my_strncmp(line, "SO", 2) == 0 && !(map->SO_texture))
		get_the_texture(line, map, 2);
	else if (ft_my_strncmp(line, "EA", 2) == 0 && !(map->EA_texture))
		get_the_texture(line, map, 3);
	else if (ft_my_strncmp(line, "WE", 2) == 0 && !(map->WE_texture))
		get_the_texture(line, map, 4);
	else if (ft_my_strncmp(line, "F", 1) == 0 && map->Floor[0] == -1)
		get_the_color(line, map, 1);
	else if (ft_my_strncmp(line, "C", 1) == 0 && map->Ceilling[0] == -1)
		get_the_color(line, map, 2);
	else if (ft_str_iswspace(line) == 0)
		return (0);
	else
		ft_error(FILE_ERROR);
	return (1);
}

/*
the fonction check_content retrieves the e texture path for each element.
*/
t_list	*check_content(t_map *map, t_list *lstmap)
{
	int		ret;

	ret = 0;
	while (lstmap && ret < 6)//changer en 6 quand sol et ciel
	{
		ret += find_the_element(map, lstmap->line);
		lstmap = ft_my_lst_delone(lstmap);
	}
	//printf("NO == |%s|\nSO == |%s|\nWE == |%s|\nEA == |%s|\n", map->NO_texture, map->SO_texture, map->WE_texture, map->EA_texture);
	//printf("Floor = |%d,%d,%d|\nCeilling = |%d,%d,%d|\n", map->Floor[0], map->Floor[1], map->Floor[2], map->Ceilling[0], map->Ceilling[1], map->Ceilling[2]);
	return (lstmap);
}
