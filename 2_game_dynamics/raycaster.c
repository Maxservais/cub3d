/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:24:10 by mservais          #+#    #+#             */
/*   Updated: 2022/01/27 10:26:36 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
