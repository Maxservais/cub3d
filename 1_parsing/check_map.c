
#include "../cub3d.h"

/*
- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and
N, S, E or W for the player’s start position and spawning orientation.
- The map must be closed/surrounded by walls, if not the program must return an error.
- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle.
- You must be able to parse any kind of map, as long as it respects the rules of the map.
*/

// static int	check_valid(t_param *param, char *str)
// {
// 	int	res;
// 	int	i;
// 	int	row;
// 	int	col;

// 	res = -1;
// 	row = 0;
// 	while (row < param->map->height)
// 	{
// 		col = 0;
// 		while (col < param->map->width)
// 		{
// 			i = 0;
// 			while (str[i] != '\0')
// 			{
// 				if (param->map->board[row][col] == str[i])
// 					res = 0;
// 				i++;
// 			}
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (res);
// }

/*
Checks if the map is surrounded by walls (note: map isn't always rectangular !!!)
*/

// static int	check_walls(t_param *param, int row, int col)
// {
// 	// if first row, can only be 1's
// 	// if last row, can only be 1's
// 	// if first or last element of a row, can only be a 1

// 	while (row < param->map->height)
// 	{
// 		col = 0;
// 		while (col < param->map->width)
// 		{
// 			if (param->map->board[row][col] != '1')
// 				return (-1);
// 			col++;
// 		}
// 		row += param->map->height - 1;
// 	}
// 	col = 0;
// 	while (col < param->map->width)
// 	{
// 		row = 0;
// 		while (row < param->map->height)
// 		{
// 			if (param->map->board[row][col] != '1')
// 				return (-1);
// 			row++;
// 		}
// 		col += param->map->width - 1;
// 	}
// 	return (0);
// }

/*
fill_board() fills the board with the map's content.
*/

static int	fill_board(t_param *p, char *filename, int row, int col)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (init_board(p))
		return (-1);
	while (row < p->map->height)
	{
		col = 0;
		get_next_line(fd, &line);
		while (col < p->map->width)
		{
			p->map->board[row][col] = line[col];
			col++;
		}
		free(line);
		row++;
	}
	close(fd);
	return (0);
}

t_list	*file_to_lst(char *filename)
{
	int	fd;
	int	ret;
	t_list	*new;
	t_list	*lstmap;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(FILE_ERROR);
	ret = 1;
	lstmap = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		new = ft_lstnew(line);
		if (!new)
			ft_error(MALLOC_ER);
		ft_lstadd_back(&lstmap, new);
	}
	if (ret == -1)
		ft_error(FILE_ERROR);
	new = ft_lstnew(line);
	if (!new)
		ft_error(MALLOC_ER);
	ft_lstadd_back(&lstmap, new);
	close (fd);
	return (lstmap);
}

/*
check_map() checks that the map is valid and that the game can be launched
*/
int	check_map(t_param *param, char *filename)
{
	t_list	*lstmap;

	lstmap = file_to_lst(filename);
	while (lstmap)
	{
		printf("%s\n", lstmap->line);
		lstmap = lstmap->next;
	}
	printf("juste avant d'exit\n");
	exit(EXIT_SUCCESS);
	param->map->height = map_height(filename);
	param->map->width = map_width(filename, 0);
	if (param->map->width <= 0 || param->map->height <= 0)
		return (-1);
	if (fill_board(param, filename, 0, 0) == -1)
		return (-1);
	// if (check_valid(param, "01NSEW") == -1)
	// {
	// 	free_board(param, param->map->height);
	// 	return (-1);
	// }
	// if (check_walls(param, 0, 0) == -1)
	// {
	// 	free_board(param, param->map->height);
	// 	return (-1);
	// }
	return (0);
}

///heyy
