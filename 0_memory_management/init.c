#include "../cub3d.h"

static void	init_map(t_param *param)
{
	param->map->width = 0;
	param->map->height = 0;
	param->map->board = NULL;
	param->map->no_texture = NULL;
	param->map->so_texture = NULL;
	param->map->ea_texture = NULL;
	param->map->we_texture = NULL;
	param->map->floor = malloc(sizeof(int) * 3);
	if (!param->map->floor)
		init_struct_fail(MALLOC_ER, 0, param);
	param->map->floor[0] = -1;
	param->map->floor[1] = -1;
	param->map->floor[2] = -1;
	param->map->ceilling = malloc(sizeof(int) * 3);
	if (!param->map->ceilling)
		init_struct_fail(MALLOC_ER, 1, param);
	param->map->ceilling[0] = -1;
	param->map->ceilling[1] = -1;
	param->map->ceilling[2] = -1;
}

void	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		ft_error(MALLOC_ER);
	init_map(param);
	param->key = malloc(sizeof(t_key));
	if (!param->key)
		init_struct_fail(MALLOC_ER, 2, param);
	param->player = malloc(sizeof(t_player));
	if (!param->player)
		init_struct_fail(MALLOC_ER, 3, param);
	param->txt = malloc(sizeof(t_texture) * 4);
	if (!param->txt)
		init_struct_fail(MALLOC_ER, 4, param);
	param->player->one = 0;
}

void	init_board(char **board, int nb)
{
	int	i;

	i = -1;
	while (++i <= nb)
		board[i] = NULL;
}

int	load_textures(t_param *p)
{
	int		i;
	char	**files;

	files = malloc(sizeof(char *) * 4);
	if (!files)
		return (-1);
	files[WEST] = p->map->we_texture;
	files[EAST] = p->map->ea_texture;
	files[NORTH] = p->map->no_texture;
	files[SOUTH] = p->map->so_texture;
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
	free(files);
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
