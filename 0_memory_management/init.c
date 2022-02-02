
#include "../cub3d.h"

int	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		return (-1);
	param->key = malloc(sizeof(t_key));
	if (!param->key)
	{
		free(param->map);
		return (-1);
	}
	param->player = malloc(sizeof(t_player));
	if (!param->player)
	{
		free(param->key);
		free(param->map);
		return (-1);
	}
	// That's where I can make the player look left/right or top/down
	param->player->pa = 0;
	param->texture = malloc(sizeof(t_texture) * 4);
	if (!param->texture)
	{
		free(param->player);
		free(param->key);
		free(param->map);
		return (-1);
	}
	return (0);
}

int	init_board(t_param *p)
{
	int	row;

	p->map->board = malloc(sizeof(char *) * p->map->height);
	if (!p->map->board)
		return (1);
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

int	load_textures(t_param *p)
{
	int		i;
	char	**files;

	files = malloc(sizeof(char *) * 4);
	if (!files)
		return (-1);
	files[WEST] = "textures/west.xpm";
	files[EAST] = "textures/east.xpm";
	files[NORTH] = "textures/north.xpm";
	files[SOUTH] = "textures/south.xpm";
	i = 0;
	while (i < 4)
	{
		p->texture[i].img_ptr = mlx_xpm_file_to_image(p->mlx_ptr, files[i], &p->texture[i].width, &p->texture[i].height);
		if (!p->texture[i].img_ptr)
			return (-1);
		p->texture[i].img_addr = mlx_get_data_addr(p->texture[i].img_ptr, &p->texture[i].bits_per_pixel, &p->texture[i].line_length, &p->texture[i].endian);
		i++;
	}
	return (0);
}
