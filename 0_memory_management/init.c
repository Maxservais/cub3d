
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
	param->key->key_up = 0;
	param->key->key_down = 0;
	param->key->key_left = 0;
	param->key->key_right = 0;
	param->key->key_arrow_left = 0;
	param->key->key_arrow_right = 0;
	param->player = malloc(sizeof(t_player));
	if (!param->player)
	{
		free(param->key);
		free(param->map);
		return (-1);
	}
	param->player->pa = 0;
	param->player->pdx = cos(param->player->pa) * SPEED;
	param->player->pdy = sin(param->player->pa) * SPEED;
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

int	load_textures(t_param *p)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		// replace PATH_TO_TEXTURE ONCE PARSING IS DONE
		p->texture[i].img_ptr = mlx_xpm_file_to_image(p->mlx_ptr, PATH_TO_TEXTURE, &p->texture[i].width, &p->texture[i].height);
		if (!p->texture[i].img_ptr)
			return (-1); // ERROR LOADING TEXTURE, PRINT TO STDERR, FREE EVERYTHING AND EXIT
		p->texture[i].img_addr = mlx_get_data_addr(p->texture[i].img_ptr, p->texture[i].bits_per_pixel, p->texture[i].line_length, p->texture[i].endian);
		i++;
	}
	return (0);
}
