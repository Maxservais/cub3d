
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
		{
			write(1, "Texture not valid\n", ft_strlen("Texture not valid\n"));
			return (-1);
		}
		p->texture[i].img_addr = mlx_get_data_addr(p->texture[i].img_ptr, &p->texture[i].bits_per_pixel, &p->texture[i].line_length, &p->texture[i].endian);
		i++;
	}
	return (0);
}

void	initialize_player_pos(t_param *p)
{
	int	row;
	int	col;

	row = 0;
	while (row < p->map->height)
	{
		col = 0;
		while (col < p->map->width)
		{
			if (p->map->board[row][col] == 'N' || p->map->board[row][col] == 'S' || p->map->board[row][col] == 'E' || p->map->board[row][col] == 'W')
			{
				p->player->px = (float)col + PLAYER_OFFSET;
				p->player->py = (float)row + PLAYER_OFFSET;
			}
			if (p->map->board[row][col] == 'N')
				p->player->pa = 3 * PI / 2;
			else if (p->map->board[row][col] == 'S')
				p->player->pa = PI / 2;
			else if (p->map->board[row][col] == 'W')
				p->player->pa = PI;
			else if (p->map->board[row][col] == 'E')
				p->player->pa = 0.0;
			col++;
		}
		row++;
	}
}
