
#include "../cub3d.h"

int	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		return (-1);
	param->key = malloc(sizeof(t_key));
	if (!param->key)
		return (-1);
	param->key->key_up = 0;
	param->key->key_down = 0;
	param->key->key_left = 0;
	param->key->key_right = 0;
	param->key->key_arrow_left = 0;
	param->key->key_arrow_right = 0;
	param->player = malloc(sizeof(t_player));
	if (!param->player)
	{
		free(param->map);
		return (-1);
	}
	param->player->pa = 0;
	param->player->pdx = cos(param->player->pa) * SPEED;
	param->player->pdy = sin(param->player->pa) * SPEED;
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
