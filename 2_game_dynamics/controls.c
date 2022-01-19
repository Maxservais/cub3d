/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:26:06 by mservais          #+#    #+#             */
/*   Updated: 2022/01/19 18:18:51 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_win(t_param *param)
{
	// free everything

	// destroy window & exit
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	exit(0);
}

int	deal_key(int key, t_param *p)
{
	if (key == ESCAPE)
		close_win(p);
	if (key == UP /*&& !try_move(p, p->player->x, p->player->y - 1, 0)*/)
	{
		erase_player(p);
		p->player->y -= BLOC_SIZE;
	}
	else if (key == DOWN /*&& !try_move(p, p->player->x, p->player->y + 1, 0)*/)
	{
		erase_player(p);
		p->player->y += BLOC_SIZE;
	}	
	else if (key == LEFT /*&& !try_move(p, p->player->x - 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->x -= BLOC_SIZE;
	}
	else if (key == RIGHT /*&& !try_move(p, p->player->x + 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->x += BLOC_SIZE;
	}
	display(p);
	return (0);
}
