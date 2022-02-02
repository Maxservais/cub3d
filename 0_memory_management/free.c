
#include "../cub3d.h"

int	free_board(t_param *p, int n)
{
	while (n > 0)
	{
		free(p->map->board[n - 1]);
		n--;
	}
	free(p->map->board);
	return (1);
}

int	free_structs(t_param *param)
{
	free(param->texture);
	free(param->player);
	free(param->key);
	free(param->map);
	return (1);
}

int	free_all(t_param *param)
{
	free_board(param, param->map->height);
	free(param->texture);
	free(param->player);
	free(param->key);
	free(param->map);
	return (1);
}
