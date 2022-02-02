
#include "../cub3d.h"

/*
get_col() gets the texel's column (the x position)
*/

int	get_col(t_param *p, t_ray *ray)
{
	int	col;

	if (ray->vertical == TRUE)
		col = (int)((1.0 - (ray->intersect_y - (int)ray->intersect_y)) * (float)p->texture[0].width);
	else
		col = (int)((ray->intersect_x - (int)ray->intersect_x) * (float)p->texture[0].width);
	return (col);
}

/*
draw_vert_line() draws a single vertical line.
*/

void	draw_vert_line(t_param *p, t_ray *ray, int i)
{
	int		k;
	int		j;
	int		col;
	// int		wall; // used to find which texture (north, south, west, east) should be displayed
	float	row;
	float	step;

	k = 0;
	j = (int)((WINDOW_HEIGHT / 2.0) - (ray->line_height / 2.0));
	while (k <= j)
	{
		my_mlx_pixel_put(p, i, k, CEILING);
		k++;
	}
	row = 0.0;
	col = get_col(p, ray);
	// How much to increase the texture coordinate per screen pixel
	step = p->texture[0].height / ray->line_height;
	while (j <= (int)((WINDOW_HEIGHT / 2.0) + (ray->line_height / 2.0)))
	{
		if (j <= WINDOW_HEIGHT && j >= 0)
			my_mlx_pixel_put(p, i, j, get_color(&p->texture[0], col, row));
		j++;
		row += step;
	}
	while (j <= WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(p, i, j, FLOOR);
		j++;
	}
}

/*
draw_walls() draws a series of vertical line, giving the impression of walls.
*/

void	draw_walls(t_param *p, t_ray *ray)
{
	int		i;
	float	ra;
	float	len;

	ra = p->player->pa - DR * (FOV / 2);
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	i = 0 - WINDOW_WIDTH / 2;
	while (i < WINDOW_WIDTH / 2)
	{
		len = len_ray(p, ray, ra) * cos(ra - p->player->pa);
		ray->line_height = (WINDOW_HEIGHT / len);
		draw_vert_line(p, ray, i + WINDOW_WIDTH / 2);
		ra += ((float)FOV / (float)WINDOW_WIDTH) * PI / 180.0;
		i++;
	}
}

/*
display() renders all the elements on screen, including our 2D minimap.
*/

int	display(void *param)
{
	t_param *p;
	t_ray	ray;

	p = (t_param *)param;
	update_pos(p);
	draw_walls(p, &ray);
	draw_minimap(p, &ray);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	return (0);
}
