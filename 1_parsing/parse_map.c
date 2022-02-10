#include "../cub3d.h"

static void	delete_wspace_in_the_map(t_list **tmp)
{
	t_list	*tmptmp;

	tmptmp = *tmp;
	*tmp = (*tmp)->next;
	ft_my_lst_delone(tmptmp);
}

static void	lst_just_map(t_map *map, t_list **lstmap, t_param *param)
{
	t_list	*tmp;
	int		tmpw;

	tmp = *lstmap;
	while (tmp && (ft_str_iswspace(tmp->line)) == 0)
		delete_wspace_in_the_map(&tmp);
	if (!tmp)
		free_texture(*lstmap, param, FILE_ER, 0);
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
			free_texture(tmp, param, FILE_ER, 1);
		delete_wspace_in_the_map(&tmp);
	}
}

static char	*copy_the_line_of_the_map(int width, char *line)
{
	char	*str;
	int		i;
	int		len;

	str = malloc(sizeof(char) * (width + 1));
	if (!str)
		return (NULL);
	len = ft_strlen(line);
	i = 0;
	while (i < width)
	{
		if (i < len)
		{
			if (ft_is_wspace(line[i]))
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

static char	**copy_the_map(t_map *map, t_list *lstmap, t_param *param)
{
	char	**board;
	int		i;

	i = 0;
	board = malloc(sizeof (char *) * (map->height + 1));
	if (!board)
		free_texture(lstmap, param, MALLOC_ER, 1);
	init_board(board, map->height);
	while (i < (map->height - 1))
	{
		board[i] = copy_the_line_of_the_map(map->width, lstmap->line);
		if (!board[i])
			free_board(param, lstmap, MALLOC_ER);
		lstmap = lstmap->next;
		ft_my_lst_delone(lstmap->before);
		i++;
	}
	board[i] = copy_the_line_of_the_map(map->width, lstmap->line);
	if (!board[i])
		free_board(param, lstmap, MALLOC_ER);
	ft_my_lst_delone(lstmap);
	return (board);
}

void	parse_map(t_map *map, t_list *lstmap, t_param *param)
{
	lst_just_map(map, &lstmap, param);
	map->board = copy_the_map(map, lstmap, param);
	check_map(param, map->board);
	if (param->player->one == 0)
		free_board(param, NULL, FILE_ER);
}
