
#include "../cub3d.h"

/*
draw_player() draws our player on the 2D minimap.
*/

void	draw_player(t_param *param)
{
	int	p_width;
	int	p_height;

	p_height = 0;
	while (p_height < 10)
	{
		p_width = 0;
		while (p_width < 10)
		{
			my_mlx_pixel_put(param, param->player->px * BLOC_SIZE + p_width, param->player->py * BLOC_SIZE + p_height, 0x000000FF);
			p_width++;
		}
		p_height++;
	}
}

/*
draw_tile() draws one tile at location (x, y) of the 2D minimap.
*/

void	draw_tile(t_param *param, int x, int y, int color)
{
	int	width;
	int	height;

	height = 0;
	while (height < BLOC_SIZE - 1)
	{
		width = 0;
		while (width < BLOC_SIZE - 1)
		{
			my_mlx_pixel_put(param, x * BLOC_SIZE + width, y * BLOC_SIZE + height, color);
			width++;
		}
		height++;
	}
}

/*
draw_map2d() draws a 2D minimap with tiles and our player.
*/

void	draw_map2d(t_param *param)
{
	int	row;
	int	col;

	row = 0;
	while (row < param->map->height)
	{
		col = 0;
		while (col < param->map->width)
		{
			if (param->map->board[row][col] == '1')
				draw_tile(param, col, row, 0x00FF0000);
			else // (param->map->board[row][col] == '0')
				draw_tile(param, col, row, 0x00FFFFFF);
			col++;
		}
		row++;
	}
}

/*
draw_drays() draws the rays around the player on the minimap.
*/

void	draw_rays(t_param *p, t_ray *ray)
{
	int		i;
	float	ra;

	ra = p->player->pa - DR * 30.0;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	i = 0 - FOV / 2;
	while (i < FOV / 2)
	{
		len_ray(p, ray, ra);
		draw_line(p, p->player->px * BLOC_SIZE + 5, p->player->py * BLOC_SIZE + 5, ray->intersect_x * BLOC_SIZE, ray->intersect_y * BLOC_SIZE);
		ra += DR;
		i++;
	}
}

/*
draw_minimap() draws our minimap in the top-left corner of the window with the player's rays.
*/

void	draw_minimap(t_param *p, t_ray *ray)
{
	draw_map2d(p);
	draw_player(p);
	draw_rays(p, ray);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
