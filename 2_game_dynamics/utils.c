#include "../cub3d.h"

/*
my_mlx_pixel_put() is our own version of the pixel_put function of the minilibX.
It sends the output to a buffer before it is rendered.
*/

void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = param->img_addr + (y * param->line_length
				+ x * (param->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
get_color() retrieves the texel 
(a texture pixel is the fundamental unit of a texture map).
*/

int	get_color(t_texture *text, int x, int y)
{
	int		color;
	char	*dst;

	dst = text->img_addr + (y * text->l_len + x * (text->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

/*
rgb_to_hex() stores the appropriate bits of each
color and convets it to hexadecimal.
*/

unsigned long long	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

/*
draw_line() draws a straight line from a point located at (x0, y0)
to a point located at (x1, y1).
It is implemented as Bresenham's line algorithm.
*/

// void	draw_line(t_param *param, int x0, int y0, int x1, int y1)
// {
// 	int	dx;
// 	int	dy;
// 	int	sx;
// 	int	sy;
// 	int	err;
// 	int	e2;

// 	dx = abs (x1 - x0);
// 	dy = -abs (y1 - y0);
// 	if (x0 < x1)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (y0 < y1)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	err = dx + dy;
// 	while (1)
// 	{
// 		my_mlx_pixel_put(param, x0, y0, 0x006A0DAD);
// 		e2 = 2 * err;
// 		if (e2 >= dy)
// 		{
// 			if (x0 == x1)
// 				break ;
// 			err += dy;
// 			x0 += sx;
// 		}
// 		if (e2 <= dx)
// 		{
// 			if (y0 == y1)
// 				break ;
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }
