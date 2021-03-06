#include "../cub3d.h"

static void	get_the_texture(t_list *lstmap, t_param *param, int identifier)
{
	if (identifier == 1)
	{
		param->map->no_texture = ft_my_strlcpy(lstmap->line);
		if (!param->map->no_texture)
			free_texture(lstmap, param, FILE_ER, 1);
	}
	else if (identifier == 2)
	{
		param->map->so_texture = ft_my_strlcpy(lstmap->line);
		if (!param->map->so_texture)
			free_texture(lstmap, param, FILE_ER, 1);
	}
	else if (identifier == 3)
	{
		param->map->ea_texture = ft_my_strlcpy(lstmap->line);
		if (!param->map->ea_texture)
			free_texture(lstmap, param, FILE_ER, 1);
	}
	else if (identifier == 4)
	{
		param->map->we_texture = ft_my_strlcpy(lstmap->line);
		if (!param->map->we_texture)
			free_texture(lstmap, param, FILE_ER, 1);
	}
}

static void	color_in(int *get, char **str, t_list *lstmap, t_param *param)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		get[i] = ft_atoi(str[i]);
		if (get[i] < 0)
			get[i] = get[i] * (-1);
		if (get[i] > 255)
			free_texture(lstmap, param, FILE_ER, 1);
	}
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

static void	get_the_color(t_list *lstmap, t_param *param, int identifier)
{
	int		i;
	int		j;
	char	**str;
	char	*line;

	line = lstmap->line;
	i = pass_the_f_or_c(line, lstmap, param);
	j = i;
	while (line[++i])
	{
		if (line[i] != ',' && !(ft_isdigit(line[i])) \
		&& !(ft_is_wspace(line[i])) && line[i] != '-')
			free_texture(lstmap, param, FILE_ER, 1);
	}
	i = ++j;
	str = ft_split(&line[i], ',');
	if (!str)
		free_texture(lstmap, param, FILE_ER, 1);
	if (str[3] || !(str[0]) || !(str[1]) || !(str[2]))
		free_texture(lstmap, param, FILE_ER, 1);
	if (identifier == 1)
		color_in(param->map->floor, str, lstmap, param);
	if (identifier == 2)
		color_in(param->map->ceilling, str, lstmap, param);
}

static int	find_the_element(t_map *map, t_list *lstmap, t_param *param)
{
	char	*line;

	line = lstmap->line;
	if (ft_my_strncmp(line, "NO", 2) == 0 && !(map->no_texture))
		get_the_texture(lstmap, param, 1);
	else if (ft_my_strncmp(line, "SO", 2) == 0 && !(map->so_texture))
		get_the_texture(lstmap, param, 2);
	else if (ft_my_strncmp(line, "EA", 2) == 0 && !(map->ea_texture))
		get_the_texture(lstmap, param, 3);
	else if (ft_my_strncmp(line, "WE", 2) == 0 && !(map->we_texture))
		get_the_texture(lstmap, param, 4);
	else if (ft_my_strncmp(line, "F", 1) == 0 && map->floor[0] == -1)
		get_the_color(lstmap, param, 1);
	else if (ft_my_strncmp(line, "C", 1) == 0 && map->ceilling[0] == -1)
		get_the_color(lstmap, param, 2);
	else if (ft_str_iswspace(line) == 0)
		return (0);
	else
		free_texture(lstmap, param, FILE_ER, 1);
	return (1);
}

t_list	*check_content(t_map *map, t_list *lstmap, t_param *param)
{
	int		ret;

	ret = 0;
	while (lstmap && ret < 6)
	{
		ret += find_the_element(map, lstmap, param);
		lstmap = ft_my_lst_delone(lstmap);
	}
	if (ret < 6 || !lstmap)
	{
		if (!lstmap)
			free_texture(NULL, param, FILE_ER, 0);
		free_texture(lstmap, param, FILE_ER, 1);
	}
	return (lstmap);
}
