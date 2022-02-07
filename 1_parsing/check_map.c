
#include "../cub3d.h"

/*
- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and
N, S, E or W for the player’s start position and spawning orientation.
- The map must be closed/surrounded by walls, if not the program must return an error.
- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle.
- You must be able to parse any kind of map, as long as it respects the rules of the map.
*/

/*
void	check_map(t_map *map, t_list *lstmap)
{
	int		player;

	player = 0;
	while (lstmap && ft_is_a_map(lstmap->line))
		lstmap = ft_my_lst_delone(lstmap);
	map->height = ft_my_lst_size(lstmap);
	while (lstmap)
	{
		printf("%s\n", lstmap->line);
		lstmap = lstmap->next;
	}
	printf("height == %d\n", map->height); //probleme pour recupere la hauteur de la map

	write(1, "couocu\n", 7);
	exit(EXIT_SUCCESS);
}
*/

void	check_map(t_map *map, t_list **lstmap)
{
	t_list	*tmp;
	t_list	*tmptmp;
	int		height;
	int		width;
	int		tmpw;

	tmp = *lstmap;
	while (tmp && (ft_str_iswspace(tmp->line))== 0)
	{
		tmptmp = tmp;
		tmp = tmp->next;
		ft_my_lst_delone(tmptmp);
	}
	*lstmap = tmp;
	height = 0;
	width = 0;
	while (tmp && ft_is_a_map(tmp->line) == 0)
	{
		height++;
		tmpw = ft_strlen(tmp->line);
		if (tmpw > width)
			width = tmpw;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (ft_str_iswspace(tmp->line) == 1)
			ft_error(FILE_ERROR);
		tmptmp = tmp;
		tmp = tmp->next;
		ft_my_lst_delone(tmptmp);
	}
	map->height = height;
	map->width = width;
	printf("height == %d\n", height);
	printf("width == %d\n", width);
	printf("------\n");
	while (*lstmap)
	{
		printf("%s\n", (*lstmap)->line);
		*lstmap = (*lstmap)->next;
	}
	printf("------\n");
	map->height = 10;
}
