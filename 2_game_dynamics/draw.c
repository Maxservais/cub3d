/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:37:53 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 19:05:22 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
my_mlx_pixel_put is our own version of the pixel_put function of the minilibX
*/

static void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
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
			my_mlx_pixel_put(param, param->player->x + x_len, param->player->y + y_len, 0x00FF0000);
			x_len++;
		}
		y_len++;
	}
}

void	display(t_param *p)
{
	draw_player(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}