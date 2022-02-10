#include "../cub3d.h"

/*
get_col() gets the texel's column (the x position) and makes sure that
the correct wall is displayed (north, south, west or south faces).
*/

static int	get_col(t_param *p, t_ray *ray, int *col, float angle)
{
	int	wall_id;

	wall_id = 0;
	if (ray->vertical == TRUE && cos(angle) > 0)
		wall_id = WEST;
	else if (ray->vertical == TRUE)
		wall_id = EAST;
	else if (sin(angle) > 0)
		wall_id = NORTH;
	else
		wall_id = SOUTH;
	if (ray->vertical == TRUE && cos(angle) > 0)
		*col = (int)((1.0 - (ray->intersect_y - (int)ray->intersect_y))
				* (float)p->txt[0].width);
	else if (ray->vertical == TRUE && cos(angle) < 0)
		*col = (int)((ray->intersect_y - (int)ray->intersect_y)
				* (float)p->txt[0].width);
	else if (ray->vertical == FALSE && sin(angle) > 0)
		*col = (int)((1.0 - (ray->intersect_x - (int)ray->intersect_x))
				* (float)p->txt[0].width);
	else
		*col = (int)((ray->intersect_x - (int)ray->intersect_x)
				* (float)p->txt[0].width);
	return (wall_id);
}

/*
draw_floor_ceiling() draws a line (that when put together
with other vertical lines, makes up the floor and ceiling)
*/

static void	draw_floor_ceiling(t_param *p, t_ray *ray, int i)
{
	int		k;
	int		j;

	k = 0;
	j = (int)((WIN_HEIGHT / 2.0) - (ray->line_height / 2.0));
	while (k < j)
	{
		my_mlx_pixel_put(p, i, k, rgb_to_hex(p->map->ceilling[0],
				p->map->ceilling[1], p->map->ceilling[2]));
		k++;
	}
	j = (int)((WIN_HEIGHT / 2.0) + (ray->line_height / 2.0));
	while (j <= WIN_HEIGHT)
	{
		my_mlx_pixel_put(p, i, j, rgb_to_hex(p->map->floor[0],
				p->map->floor[1], p->map->floor[2]));
		j++;
	}
}

/*
draw_vert_line() draws a single vertical line of the texture.
*/

static void	draw_vert_line(t_param *p, t_ray *ray, int i, float angle)
{
	int		j;
	int		col;
	int		wall_id;
	float	row;
	float	step;

	draw_floor_ceiling(p, ray, i);
	row = 0.0;
	wall_id = get_col(p, ray, &col, angle);
	step = p->txt[wall_id].height / ray->line_height;
	j = (int)((WIN_HEIGHT / 2.0) - (ray->line_height / 2.0));
	while (j < (int)((WIN_HEIGHT / 2.0) + (ray->line_height / 2.0)))
	{
		if (j <= WIN_HEIGHT && j >= 0)
			my_mlx_pixel_put(p, i, j, get_color(&p->txt[wall_id], col, row));
		j++;
		row += step;
	}
}

/*
draw_walls() draws a series of vertical line, giving the impression of walls.
*/

static void	draw_walls(t_param *p, t_ray *ray)
{
	int		i;
	float	ra;
	float	len;

	ra = p->player->pa - DR * (FOV / 2);
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	i = 0 - WIN_WIDTH / 2;
	while (i < WIN_WIDTH / 2)
	{
		len = len_ray(p, ray, ra) * cos(ra - p->player->pa);
		ray->line_height = (WIN_HEIGHT / len);
		draw_vert_line(p, ray, i + WIN_WIDTH / 2, ra);
		ra += ((float)FOV / (float)WIN_WIDTH) * PI / 180.0;
		i++;
	}
}

/*
display() renders all the elements on screen, including our 2D minimap.
*/

int	display(void *param)
{
	t_param	*p;
	t_ray	ray;

	p = (t_param *)param;
	update_pos(p);
	draw_walls(p, &ray);
	draw_minimap(p, &ray);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	return (0);
}
