#include "../cub3d.h"

/*
draw_drays() draws the rays around the player on the minimap.
*/

void	draw_rays(t_param *p, t_ray *ray)
{
	int		i;
	float	ra;

	ra = p->player->pa - DR * FOV / 2;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	i = 0 - FOV / 2;
	while (i < FOV / 2)
	{
		len_ray(p, ray, ra);
		draw_line(p, p->player->px * p->tile_size,
			p->player->py * p->tile_size, ray->intersect_x * p->tile_size,
			ray->intersect_y * p->tile_size);
		ra += DR;
		i++;
	}
}

/*
draw_player() draws our player on the 2D minimap.
*/

void	draw_player(t_param *param)
{
	int	p_width;
	int	p_height;

	p_height = 0;
	while (p_height < 0.5 * param->tile_size)
	{
		p_width = 0;
		while (p_width < 0.5 * param->tile_size)
		{
			my_mlx_pixel_put(param, (param->player->px - PLAYER_OFFSET)
				* param->tile_size + p_width,
				(param->player->py - PLAYER_OFFSET) * param->tile_size
				+ p_height, 0x000000FF);
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
	while (height < param->tile_size)
	{
		width = 0;
		while (width < param->tile_size)
		{
			if (width == param->tile_size - 1 || height == param->tile_size - 1)
				my_mlx_pixel_put(param, x * param->tile_size + width,
					y * param->tile_size + height, BLACK);
			else
				my_mlx_pixel_put(param, x * param->tile_size + width,
					y * param->tile_size + height, color);
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
				draw_tile(param, col, row, rgb_to_hex(135, 206, 235));
			else
				draw_tile(param, col, row, rgb_to_hex(255, 255, 255));
			col++;
		}
		row++;
	}
}

/*
draw_minimap() draws our minimap in the top-left corner of the window
with the player's rays.
*/

void	draw_minimap(t_param *p, t_ray *ray)
{
	draw_map2d(p);
	draw_player(p);
	draw_rays(p, ray);
}
