
#include "../cub3d.h"

/*
my_mlx_pixel_put() is our own version of the pixel_put function of the minilibX.
It sends the output to a buffer before it is rendered.
*/

void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = param->img_addr + (y * param->line_length + x * (param->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
	// int	i;
	// if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	// {
	// 	i = (x * param->bits_per_pixel / 8) + (y * param->line_length);
	// 	param->img_addr[i] = color;
	// 	param->img_addr[++i] = color >> 8;
	// 	param->img_addr[++i] = color >> 16;
	// }
}

int		get_color(t_texture *text, int x, int y)
{
	int		color;
	char	*dst;

	dst = text->img_addr + (y * text->line_length + x * (text->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
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
		my_mlx_pixel_put(param, x0, y0, LINE);
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
