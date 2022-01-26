/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/26 17:48:32 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
my_mlx_pixel_put() is our own version of the pixel_put function of the minilibX.
It sends the output to a buffer before it is rendered.
*/

void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->img_addr + (y * param->line_length + x * (param->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
draw_line() draws a straight line from a point located at (x0, y0) to a point located at (x1, y1).
It is implemented as Bresenham's line algorithm.
*/

void	draw_line(t_param *param, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs (x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs (y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(param, x0, y0, 0x006A0DAD);
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break;
			err += dx;
			y0 += sy;
		}
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

/*
len_ray() computes the distance that separates the player from the wall with a specified angle
Credits:
- https://lodev.org/cgtutor/raycasting.html
- https://www.youtube.com/watch?v=NbSee-XM7WA
*/

float	len_ray(t_param *param, t_ray *ray, float angle)
{
	float	len;
	float	dist_max;

	// ray' starting position is the location of the player
	ray->start_x = param->player->px;
	ray->start_y = param->player->py;
	// direction of the ray
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	// Scaling factor that links our hypotenus to a step change of unit in either direction
	ray->step_size_x = sqrt(1.0 + pow(ray->dir_y / ray->dir_x, 2));
	ray->step_size_y = sqrt(1.0 + pow(ray->dir_x / ray->dir_y, 2));
	// Keep track of tile I am located in
	ray->map_check_x = (int)ray->start_x;
	ray->map_check_y = (int)ray->start_y;
	ray->distance = 0;
	ray->collision_detected = FALSE;
	ray->vertical = FALSE;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->length_x = (ray->start_x - (float)ray->map_check_x) * ray->step_size_x;		
	}
	else
	{
		ray->step_x = 1;
		ray->length_x = ((float)(ray->map_check_x + 1) - ray->start_x) * ray->step_size_x;		
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->length_y = (ray->start_y - (float)ray->map_check_y) * ray->step_size_y;
	}
	else
	{
		ray->step_y = 1;
		ray->length_y = ((float)(ray->map_check_y + 1) - ray->start_y) * ray->step_size_y;
	}
	if (param->map->width > param->map->height)
		dist_max = param->map->width;
	else
		dist_max = param->map->height;
	while (ray->collision_detected == FALSE && ray->distance < dist_max)
	{
		// Walk along shortest path
		if (ray->length_x < ray->length_y)
		{
			ray->map_check_x += ray->step_x;
			ray->distance = ray->length_x;
			ray->length_x += ray->step_size_x;
			ray->vertical = TRUE;
		}
		else
		{
			ray->map_check_y += ray->step_y;
			ray->distance = ray->length_y;
			ray->length_y += ray->step_size_y;
			ray->vertical = FALSE;
		}
		// Test tile at new test point
		if (ray->map_check_x >= 0 && ray->map_check_x < param->map->width && ray->map_check_y >= 0 && ray->map_check_y < param->map->height)
		{
			if (param->map->board[ray->map_check_y][ray->map_check_x] == '1')
			{
				ray->collision_detected = TRUE;
			}
		}
	}
	if (ray->collision_detected == TRUE)
	{
		ray->intersect_x = ray->start_x + (ray->dir_x * ray->distance);
		ray->intersect_y = ray->start_y + (ray->dir_y * ray->distance);
	}
	len = sqrt(pow(ray->intersect_x - ray->start_x, 2) + pow(ray->intersect_y - ray->start_y, 2));
	return (len);
}

/*
draw_wall() draws a series of vertical line, giving the impression that a 'wall' is displayed.
*/

void	draw_wall(t_param *p, t_ray *ray, int i)
{
	
	int	j;

	j = (int)((WINDOW_HEIGHT / 2.0) - (ray->line_height / 2.0));
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
}

/*
display() renders all the elements on screen, including our 2D minimap.
*/

int	display(void *param)
{
	t_param *p;
	t_ray	ray;
	int		i;
	float	ra;
	float	len;

	p = (t_param *)param;
	ft_bzero(p->img_addr, WINDOW_WIDTH * WINDOW_HEIGHT * (p->bits_per_pixel / 8));
	ra = p->player->pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	i = 0 - WINDOW_WIDTH / 2;
	while (i < WINDOW_WIDTH / 2)
	{
		len = len_ray(p, &ray, ra);
		ray.line_height = (int)(WINDOW_HEIGHT / len); // Why cast to int?
		draw_wall(p, &ray, i + WINDOW_WIDTH / 2);
		ra += ((float)FOV / (float)WINDOW_WIDTH) * PI / 180.0;
		i++;
	}
	draw_minimap(p, &ray);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	return (0);
}
