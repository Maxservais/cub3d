
#include "cub3d.h"

/*
Function's goal is to launch the game:
- mlx_init() initializes the connection and returns an identifier
of the connection that is established with the graphical server;
- The  mlx_new_window() function creates a new window on the screen,
using the size_x and size_y parameters to determine its size, and title
as the text that should be displayed in the window's title bar.
*/

static int	game_start(t_param *param)
{
	param->mlx_ptr = mlx_init();
	if (!param->mlx_ptr)
		return (-1);
	param->win_ptr = mlx_new_window(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
	if (!param->win_ptr)
		return (-1);
	param->img_ptr = mlx_new_image(param->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!param->img_ptr)
		return (-1);
	param->img_addr = mlx_get_data_addr(param->img_ptr, &param->bits_per_pixel, &param->line_length, &param->endian);
	if (param->map->width > param->map->height)
		param->tile_size = (WINDOW_WIDTH * 0.4) / param->map->width;
	else
		param->tile_size = (WINDOW_HEIGHT * 0.4) / param->map->height;
	if (load_textures(param) == -1)
		return (-1);
	return (0);
}

/*
Our main function:
- returns an error when our executable file (./cub3d) isn't called with the right command-line argument;
- returns an error when there is an issue allocating memory on the Heap
- calls a function to parse the file that contains information on the map, the floor,
ceiling and walls' colors;
- launches the game;
- calls a function to draw the 2D minimap in the top-left corner;
- hooks into events to capture users' input.
*/

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2 || init_structs(&param) == -1)
	{
		printf("Usage: ./cub3d file_name\n");
		return (EXIT_FAILURE);
	}
	if (check_map(&param, argv[1]))
		return (free_structs(&param));
	if (game_start(&param) == -1)
		return (free_all(&param));
	initialize_player_pos(&param);
	mlx_hook(param.win_ptr, 2, 1L << 0, &key_press, &param);
	mlx_hook(param.win_ptr, 3, 1L << 0, &key_unpress, &param);
	mlx_hook(param.win_ptr, 17, 1L << 17, &close_win, &param);
	mlx_loop_hook(param.mlx_ptr, display, &param);
	mlx_loop(param.mlx_ptr);
	return (EXIT_SUCCESS);
}
