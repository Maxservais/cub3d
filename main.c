/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:54:10 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 14:32:29 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	main(int argc, char **argv)
{
	t_param	param;

	// Deal with input errors
	if (argc != 2)
		return (error_message());

	// Parse map and deal with errors

	// Launch game
	if (game_start(&param) == 1)
		return (EXIT_FAILURE);

	// Hook into events 
	mlx_hook(p->win_ptr, 2, 1L << 0, &deal_key, p);
	mlx_hook(p->win_ptr, 17, 1L << 17, &close_win, p);
	mlx_loop(p->mlx_ptr);
	return (EXIT_SUCCES);
}
