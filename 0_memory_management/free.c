#include "../cub3d.h"

int	free_structs(t_param *param)
{
	free(param->txt);
	free(param->player);
	free(param->key);
	free(param->map);
	return (1);
}

int	free_all(t_param *param)
{
	free_board(param, NULL, FILE_ER);
	free(param->txt);
	free(param->player);
	free(param->key);
	free(param->map);
	return (1);
}
