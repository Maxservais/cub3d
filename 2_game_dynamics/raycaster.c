#include "../cub3d.h"

/*
len_ray() computes the distance that separates the player
from the wall with a specified angle.
Credits:
- https://lodev.org/cgtutor/raycasting.html
- https://www.youtube.com/watch?v=NbSee-XM7WA
*/

static void	ray_init(t_param *p, t_ray *ray, float angle)
{
	ray->start_x = p->player->px;
	ray->start_y = p->player->py;
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->step_size_x = sqrt(1.0 + pow(ray->dir_y / ray->dir_x, 2));
	ray->step_size_y = sqrt(1.0 + pow(ray->dir_x / ray->dir_y, 2));
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->distance = 0;
	ray->collision_detected = FALSE;
	ray->vertical = FALSE;
}

static void	ray_init_bis(t_param *p, t_ray *r, float *dist_max)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->length_x = (r->start_x - (float)r->map_x) * r->step_size_x;
	}
	else
	{
		r->step_x = 1;
		r->length_x = ((float)(r->map_x + 1) - r->start_x) * r->step_size_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->length_y = (r->start_y - (float)r->map_y) * r->step_size_y;
	}
	else
	{
		r->step_y = 1;
		r->length_y = ((float)(r->map_y + 1) - r->start_y) * r->step_size_y;
	}
	if (p->map->width > p->map->height)
		*dist_max = p->map->width;
	else
		*dist_max = p->map->height;
}

static void	ray_loop(t_param *p, t_ray *r, float dist_max)
{
	while (r->collision_detected == FALSE && r->distance < dist_max)
	{
		if (r->length_x < r->length_y)
		{
			r->map_x += r->step_x;
			r->distance = r->length_x;
			r->length_x += r->step_size_x;
			r->vertical = TRUE;
		}
		else
		{
			r->map_y += r->step_y;
			r->distance = r->length_y;
			r->length_y += r->step_size_y;
			r->vertical = FALSE;
		}
		if (r->map_x >= 0 && r->map_x < p->map->width
			&& r->map_y >= 0 && r->map_y < p->map->height)
		{
			if (p->map->board[r->map_y][r->map_x] == '1')
			{
				r->collision_detected = TRUE;
			}
		}
	}
}

float	len_ray(t_param *param, t_ray *r, float angle)
{
	float	len;
	float	dist_max;

	ray_init(param, r, angle);
	ray_init_bis(param, r, &dist_max);
	ray_loop(param, r, dist_max);
	if (r->collision_detected == TRUE)
	{
		r->intersect_x = r->start_x + (r->dir_x * r->distance);
		r->intersect_y = r->start_y + (r->dir_y * r->distance);
	}
	len = sqrt(pow(r->intersect_x - r->start_x, 2)
			+ pow(r->intersect_y - r->start_y, 2));
	return (len);
}
