
#include "../cub3d.h"

static void	init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->board = NULL;
	map->NO_texture = NULL;
	map->SO_texture = NULL;
	map->EA_texture = NULL;
	map->WE_texture = NULL;
	map->Floor = malloc(sizeof(int) * 3);
	if (!map->Floor)
		ft_error(MALLOC_ER);
	map->Floor[0] = -1;
	map->Floor[1] = -1;
	map->Floor[2] = -1;
	map->Ceilling = malloc(sizeof(int) * 3);
	if (!map->Ceilling)
		ft_error(MALLOC_ER);
	map->Ceilling[0] = -1;
	map->Ceilling[1] = -1;
	map->Ceilling[2] = -1;
}

int	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		return (-1);
	init_map(param->map);
	param->player = malloc(sizeof(t_player));
	if (!param->player)
	{
		free(param->map);
		return (-1);
	}
	param->player->pa = 0;
	param->player->pdx = cos(param->player->pa) * 0.1;
	param->player->pdy = sin(param->player->pa) * 0.1;
	// param->sprite = malloc(sizeof(t_sprite));
	// if (!param->sprite)
	// {
	// 	free(param->player);
	// 	free(param->map);
	// 	return (-1);
	// }
	return (0);
}

int	init_board(t_param *p)
{
	int	row;

	p->map->board = malloc(sizeof(char *) * p->map->height);
	if (!p->map->board)
		return (-1);
	row = 0;
	while (row < p->map->height)
	{
		p->map->board[row] = malloc(sizeof(char) * p->map->width);
		if (!p->map->board[row])
			return (free_board(p, row));
		row++;
	}
	return (0);
}
