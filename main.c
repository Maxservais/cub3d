/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:54:10 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 17:46:36 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1); // Free everything that was malloced
	param->win_ptr = mlx_new_window(param->mlx_ptr,
			1200, 960, "CUB3D");
	if (!param->win_ptr)
		return (1); // Free everything that was malloced
	return (0);
}

/*
Our main function:
- returns an error when our executable file (./cub3d) isn't called with the right command-line argument;
- calls a function to parse the file that contains information on the map as well
as the floor, ceiling and walls' colors;
- launches the game;
- hooks into events to capture users' input.
*/

int	main(int argc, char **argv)
{
	t_param	param;

	// Deal with input errors and memory allocation problems
	if (argc != 2 || init_structs(&param) == -1)
	{
		printf("Usage: ./cub3d file_name\n");
		return (EXIT_FAILURE);
	}

	// Parse file and deal with errors (for elements + map)
	if (check_map(&param, argv[1]))
		return (EXIT_FAILURE); // return (free_structs(p));
	
	// Launch game
	if (game_start(&param) == 1)
		return (EXIT_FAILURE);

	// Hook into events
	mlx_hook(param.win_ptr, 2, 1L << 0, &deal_key, &param);
	mlx_hook(param.win_ptr, 17, 1L << 17, &close_win, &param);
	mlx_loop(param.mlx_ptr);
	return (EXIT_FAILURE);
}
