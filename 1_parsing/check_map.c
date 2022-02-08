
#include "../cub3d.h"

/*
- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and
N, S, E or W for the player’s start position and spawning orientation.
- The map must be closed/surrounded by walls, if not the program must return an error.
- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle.
- You must be able to parse any kind of map, as long as it respects the rules of the map.
*/

void	lst_just_map(t_map *map, t_list **lstmap)
{
	t_list	*tmp;
	t_list	*tmptmp;
	int		tmpw;

	tmp = *lstmap;
	while (tmp && (ft_str_iswspace(tmp->line))== 0)
	{
		tmptmp = tmp;
		tmp = tmp->next;
		ft_my_lst_delone(tmptmp);
	}
	if (!tmp)
		ft_error(FILE_ERROR);
	*lstmap = tmp;
	while (tmp && ft_is_a_map(tmp->line) == 0)
	{
		map->height++;
		tmpw = ft_strlen(tmp->line);
		if (tmpw > map->width)
			map->width = tmpw;
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
}

char	*copy_the_line_of_the_map(int width, char *line)
{
	char	*str;
	int		i;
	int		len;

	str = malloc(sizeof(char) * (width + 1));
	if (!str)
		ft_error(MALLOC_ER);
	len = ft_strlen(line);
	i = 0;
	while (i < width)
	{
		if (i < len)
		{
			if(ft_is_wspace(line[i]))
				str[i] = ' ';
			else
				str[i] = line[i];
		}
		else
			str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**copy_the_map(t_map *map, t_list *lstmap)
{
	char **board;
	int	i;

	i = 0;
	board = malloc(sizeof (char *) * (map->height + 1));
	if (!board)
		ft_error(MALLOC_ER);
	board[map->height] = NULL;
	while (i < (map->height - 1))
	{
		board[i] = copy_the_line_of_the_map(map->width, lstmap->line);
		lstmap = lstmap->next;
		ft_my_lst_delone(lstmap->before);
		i++;
	}
	board[i] = copy_the_line_of_the_map(map->width, lstmap->line);
	ft_my_lst_delone(lstmap);
	return (board);
}

int	check_around(char **board, int i, int j, t_map *map)
{
	if (i == 0 || j == 0 || i == map->height || j == map->width)
		return (0);
	if (board[i - 1][j] == ' ' || board[i + 1][j] == ' ' || board[i][j - 1] == ' ' || board[i][j + 1] == ' ')
		return (0);
	return (1);
}

void	check_map(t_param *param, char **board)
{
	int	i;
	int	j;

	i = -1;
	while (board[++i])
	{
		j = -1;
		while (board[i][++j])
		{
			if (board[i][j] == '0' && (check_around(board, i, j, param->map) == 0))
				ft_error(FILE_ERROR);
			else if (board[i][j] == 'N' || board[i][j] == 'E' || board[i][j] == 'S' || board[i][j] == 'W')
			{
				if (param->player->one == 1 || (check_around(board, i, j, param->map) == 0))
					ft_error(FILE_ERROR);
				param->player->one = 1;
			}
		}
	}
}

void	parse_map(t_map *map, t_list *lstmap, t_param *param)
{
	lst_just_map(map, &lstmap);
	map->board = copy_the_map(map, lstmap);
	check_map(param, map->board);
	if (param->player->one == 0)
		ft_error(FILE_ERROR);
	int test_i;
	int	test_j;

	test_i = 0;
	test_j = 0;
	while (map->board[test_i])
	{
		test_j = 0;
		while (map->board[test_i][test_j])
		{
			printf("%c", map->board[test_i][test_j]);
			test_j++;
		}
		printf("\n");
		test_i++;
	}
}
