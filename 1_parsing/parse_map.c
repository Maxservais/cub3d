#include "../cub3d.h"

static void	delete_wspace_in_the_map(t_list **tmp)
{
	t_list	*tmptmp;

	tmptmp = *tmp;
	*tmp = (*tmp)->next;
	ft_my_lst_delone(tmptmp);
}

static void	lst_just_map(t_map *map, t_list **lstmap)
{
	t_list	*tmp;
	int		tmpw;

	tmp = *lstmap;
	while (tmp && (ft_str_iswspace(tmp->line)) == 0)
		delete_wspace_in_the_map(&tmp);
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
		ft_error(MALLOC_ER);
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

static char	**copy_the_map(t_map *map, t_list *lstmap)
{
	char	**board;
	int		i;

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

void	parse_map(t_map *map, t_list *lstmap, t_param *param)
{
	lst_just_map(map, &lstmap);
	map->board = copy_the_map(map, lstmap);
	check_map(param, map->board);
	if (param->player->one == 0)
		ft_error(FILE_ERROR);
}
