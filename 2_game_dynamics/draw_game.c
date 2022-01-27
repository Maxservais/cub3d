/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/27 10:25:18 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
draw_vert_line() draws a series of vertical line, giving the impression that a 'wall' is displayed.
*/

void	draw_vert_line(t_param *p, t_ray *ray, int i)
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
		draw_vert_line(p, &ray, i + WINDOW_WIDTH / 2);
		ra += ((float)FOV / (float)WINDOW_WIDTH) * PI / 180.0;
		i++;
	}
	draw_minimap(p, &ray);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	return (0);
}
