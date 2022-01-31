
#include "../cub3d.h"

/*
draw_vert_line() draws a single vertical line.
*/

void	draw_vert_line(t_param *p, t_ray *ray, int i)
{
	int	k;
	int	j;

	k = 0;
	j = (int)((WINDOW_HEIGHT / 2.0) - (ray->line_height / 2.0));	
	while (k < j)
	{
		my_mlx_pixel_put(p, i, k, CEILING);
		k++;
	}
	while (j < (int)((WINDOW_HEIGHT / 2.0) + (ray->line_height / 2.0)))
	{
		if (j <= WINDOW_HEIGHT && j >= 0)
		{
			if (ray->vertical == TRUE)
				my_mlx_pixel_put(p, i, j, 0x0000FF00);
			else
				my_mlx_pixel_put(p, i, j, 0x0000FF00 / 2);
		}
		j++;
	}
	while (j < WINDOW_HEIGHT)
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
		len = len_ray(p, ray, ra);
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
