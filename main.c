#include "cub3d.h"

/*
Function's goal is to launch the game:
- mlx_init() initializes the connection and returns an identifier
of the connection that is established with the graphical server;
- The  mlx_new_window() function creates a new window on the screen,
using the size_x and size_y parameters to determine its size, and title
as the text that should be displayed in the window's title bar.
*/

static int	game_start(t_param *p)
{
	p->mlx_ptr = mlx_init();
	if (!p->mlx_ptr)
		return (-1);
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!p->win_ptr)
		return (-1);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!p->img_ptr)
		return (-1);
	p->img_addr = mlx_get_data_addr(p->img_ptr, &p->bits_per_pixel,
			&p->line_length, &p->endian);
	if (p->map->width > p->map->height)
		p->tile_size = (WIN_WIDTH * 0.4) / p->map->width;
	else
		p->tile_size = (WIN_HEIGHT * 0.4) / p->map->height;
	if (load_textures(p, 0) == -1)
		return (-1);
	return (0);
}

/*
Our main function:
- returns an error when our executable file (./cub3d) isn't called with
the right command-line argument;
- returns an error when there is an issue allocating memory on the Heap
- calls a function to parse the file that contains information on the map,
the floor, ceiling and walls' colors;
- launches the game;
- calls a function to draw the 2D minimap in the top-left corner;
- hooks into events to capture users' input.
*/

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		ft_error(FILENAME_ERROR);
	init_structs(&param);
	parse_file(&param, argv[1]);
	if (game_start(&param) == -1)
		free_board(&param, NULL, FILE_ER);
	initialize_player_pos(&param, 0, 0);
	mlx_hook(param.win_ptr, 2, 1L << 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 1L << 0, &key_unpress, &param);
	mlx_hook(param.win_ptr, 17, 1L << 17, &close_win, &param);
	mlx_loop_hook(param.mlx_ptr, display, &param);
	mlx_loop(param.mlx_ptr);
	return (EXIT_SUCCESS);
}
