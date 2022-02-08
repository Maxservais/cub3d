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
	param->txt = malloc(sizeof(t_texture) * 4);
	if (!param->txt)
	{
		free(param->player);
		free(param->key);
		free(param->map);
		return (-1);
	}
	// param->player->pa = 0;
	// param->player->pdx = cos(param->player->pa) * 0.1;
	// param->player->pdy = sin(param->player->pa) * 0.1;
	param->player->one = 0;
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
	files[WEST] = p->map->WE_texture;
	files[EAST] = p->map->EA_texture;
	files[NORTH] = p->map->NO_texture;
	files[SOUTH] = p->map->SO_texture;
	i = 0;
	while (i < 4)
	{
		p->txt[i].img_ptr = mlx_xpm_file_to_image(p->mlx_ptr, files[i],
				&p->txt[i].width, &p->txt[i].height);
		if (!p->txt[i].img_ptr)
		{
			write(1, "Texture not valid\n", ft_strlen("Texture not valid\n"));
			return (-1);
		}
		p->txt[i].img_addr = mlx_get_data_addr(p->txt[i].img_ptr,
				&p->txt[i].bpp, &p->txt[i].l_len, &p->txt[i].endian);
		i++;
	}
	return (0);
}

void	initialize_player_pos(t_param *p, int row, int col)
{
	while (row < p->map->height)
	{
		col = 0;
		while (col < p->map->width)
		{
			if (p->map->board[row][col] == 'N' || p->map->board[row][col] == 'S'
								|| p->map->board[row][col] == 'E'
								|| p->map->board[row][col] == 'W')
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
