/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/26 10:19:08 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
my_mlx_pixel_put is our own version of the pixel_put function of the minilibX
*/

void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->img_addr + (y * param->line_length + x * (param->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_player(t_param *param)
{
	int	x_len;
	int	y_len;

	y_len = 0;
	while (y_len < 10)
	{
		x_len = 0;
		while (x_len < 10)
		{
			my_mlx_pixel_put(param, param->player->px + x_len, param->player->py + y_len, 0x000000FF);
			x_len++;
		}
		y_len++;
	}
}

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

void	draw_tile(t_param *param, int x, int y, int color)
{
	int	x_len;
	int	y_len;

	y_len = 0;
	while (y_len < BLOC_SIZE - 1)
	{
		x_len = 0;
		while (x_len < BLOC_SIZE - 1)
		{
			my_mlx_pixel_put(param, x + x_len, y + y_len, color);
			x_len++;
		}
		y_len++;
	}
}

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
				draw_tile(param, col * BLOC_SIZE, row * BLOC_SIZE, 0x00FF0000);
			else if (param->map->board[row][col] == '0')
				draw_tile(param, col * BLOC_SIZE, row * BLOC_SIZE, 0x00FFFFFF);
			else if (param->map->board[row][col] == 'N') // add other letters
				draw_player(param);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, param->img_ptr, 0, 0);
}

/* 
Credit:
1) https://lodev.org/cgtutor/raycasting.html
2) https://www.youtube.com/watch?v=NbSee-XM7WA
*/

float	draw_rays(t_param *param, t_ray *ray, float angle)
{
	float	len;
	float	dist_max;

	// ray' starting position is the location of the player
	ray->start_x = param->player->px + 5;
	ray->start_y = param->player->py + 5;
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
		dist_max = param->map->width * BLOC_SIZE;
	else
		dist_max = param->map->height * BLOC_SIZE;
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
		if (ray->map_check_x >= 0 && ray->map_check_x < param->map->width * BLOC_SIZE && ray->map_check_y >= 0 && ray->map_check_y < param->map->height * BLOC_SIZE)
		{
			if (param->map->board[ray->map_check_y / BLOC_SIZE][ray->map_check_x / BLOC_SIZE] == '1')
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
	draw_line(param, param->player->px + 5, param->player->py + 5, ray->intersect_x, ray->intersect_y);
	len = sqrt(pow(ray->intersect_x - ray->start_x, 2) + pow(ray->intersect_y - ray->start_y, 2));
	return (len);
}

void	display(t_param *p, t_ray *ray)
{
	int		i;
	float	ra;

	ra = p->player->pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	ft_bzero(p->img_addr, p->map->width * BLOC_SIZE * p->map->height * BLOC_SIZE * (p->bits_per_pixel / 8));
	draw_map2d(p);
	draw_player(p);
	i = 0;
	while (i < 60)
	{
		draw_rays(p, ray, ra);
		ra += DR;
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
