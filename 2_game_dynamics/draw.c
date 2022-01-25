/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/25 10:40:55 by mservais         ###   ########.fr       */
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
		my_mlx_pixel_put(param, x0, y0, 0x00FFFFFF);
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

// void	draw_rays(t_param *param)
// {
// 	int		r;
// 	int		mx;
// 	int		my;
// 	int		mp;
// 	int		dof;
// 	float	rx;
// 	float	ry;
// 	float	ra;
// 	float	xo;
// 	float	yo;
// 	float	a_tan;

// 	ra = param->player->pa;
// 	r = 0;
// 	while (r < 1)
// 	{
// 		dof = 0;
// 		a_tan = -1 / tan(ra);
// 		if (ra > PI)
// 		{
// 			ry = (((int)param->player->py>>6)<<6) - 0.0001;
// 			rx = (param->player->py - ry) * a_tan + param->player->px;
// 			yo = -64;
// 			xo = -yo * a_tan;
// 		}
// 		if (ra < PI)
// 		{
// 			ry = (((int)param->player->py>>6)<<6) + 64;
// 			rx = (param->player->py - ry) * a_tan + param->player->px;
// 			yo = 64;
// 			xo = -yo * a_tan;
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = param->player->px;
// 			ry = param->player->py;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int) (rx) >>6;
// 			my = (int) (ry) >>6;
// 			mp = my * param->map->width + mx;
// 			if (mp < param->map->width * param->map->height && param->map->board[0][mp] == 1)
// 				dof = 8;
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof++;
// 			}
// 		}
// 		r++;
// 	}
// }

void	display(t_param *p)
{
	ft_bzero(p->img_addr, p->map->width * BLOC_SIZE * p->map->height * BLOC_SIZE * (p->bits_per_pixel / 8));
	draw_map2d(p);
	draw_player(p);
	draw_line(p, p->player->px + 5, p->player->py + 5, 5 + p->player->px + cos(p->player->pa) * 30, 5 + p->player->py + sin(p->player->pa) * 30);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
