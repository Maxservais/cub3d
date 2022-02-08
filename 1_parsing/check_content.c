#include "../cub3d.h"

static void	get_the_texture(char *line, t_map *map, int identifier)
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
	}
	else if (identifier == 4)
	{
		map->WE_texture = ft_my_strlcpy(line);
		if (!map->WE_texture)
			ft_error(FILE_ERROR);
	}
}

static void	color_in_floor_or_ceilling(int *get, char **str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		get[i] = ft_atoi(str[i]);
		if (get[i] < 0 || get[i] > 255)
			ft_error(COLOR_ER);
	}
}

static void	get_the_color(char *line, t_map *map, int identifier)
{
	int		i;
	char	**str;

	while (*line && !ft_isdigit(*line))
		line++;
	i = -1;
	while (line[++i])
	{
		if (line[i] != ',' && !(ft_isdigit(line[i])) \
		&& !(ft_is_wspace(line[i])))
			ft_error(FILE_ERROR);
	}
	if (!*line)
		ft_error(COLOR_ER);
	str = ft_split(line, ',');
	if (str[3])
		ft_error(FILE_ERROR);
	if (!str)
		ft_error(MALLOC_ER);
	if (identifier == 1)
		color_in_floor_or_ceilling(map->Floor, str);
	if (identifier == 2)
		color_in_floor_or_ceilling(map->Ceilling, str);
}

static int	find_the_element(t_map *map, char *line)
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

t_list	*check_content(t_map *map, t_list *lstmap)
{
	int		ret;

	ret = 0;
	while (lstmap && ret < 6)
	{
		ret += find_the_element(map, lstmap->line);
		lstmap = ft_my_lst_delone(lstmap);
	}
	if (ret < 6 || !lstmap)
		ft_error(FILE_ERROR);
	return (lstmap);
}
