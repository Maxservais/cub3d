/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/20 10:33:28 by mservais         ###   ########.fr       */
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

void	erase_player(t_param *param)
{
	int	x_len;
	int	y_len;

	y_len = 0;
	while (y_len < 10)
	{
		x_len = 0;
		while (x_len < 10)
		{
			my_mlx_pixel_put(param, param->player->px + x_len, param->player->py + y_len, 0x00FFFFFF);
			x_len++;
		}
		y_len++;
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

void	display(t_param *p)
{
	draw_player(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
