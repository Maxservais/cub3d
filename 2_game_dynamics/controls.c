/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:26:06 by mservais          #+#    #+#             */
/*   Updated: 2022/01/20 14:46:31 by mservais         ###   ########.fr       */
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
		p->player->px += p->player->pdx;
		p->player->py += p->player->pdy;
		// p->player->py -= BLOC_SIZE;
	}
	else if (key == DOWN /*&& !try_move(p, p->player->x, p->player->y + 1, 0)*/)
	{
		erase_player(p);
		p->player->px -= p->player->pdx;
		p->player->py -= p->player->pdy;
	}	
	else if (key == LEFT /*&& !try_move(p, p->player->x - 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->px -= cos(p->player->pa + PI / 2) * 5;
		p->player->py -= sin(p->player->pa + PI / 2) * 5;
		// p->player->px -= BLOC_SIZE;
	}
	else if (key == RIGHT /*&& !try_move(p, p->player->x + 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->px += cos(p->player->pa + PI / 2) * 5;
		p->player->py += sin(p->player->pa + PI / 2) * 5;
		
		// p->player->px += BLOC_SIZE;
	}
	else if (key == LEFT_ARROW /*&& !try_move(p, p->player->x - 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->pa-=0.1;
		if (p->player->pa < 0) 
			p->player->pa += 2 * PI;
		p->player->pdx = cos(p->player->pa) * 5;
		p->player->pdy = sin(p->player->pa) * 5;
	}
	else if (key == RIGHT_ARROW /*&& !try_move(p, p->player->x + 1, p->player->y, 0)*/)
	{
		erase_player(p);
		p->player->pa+=0.1;
		if (p->player->pa > 2 * PI)
			p->player->pa -= 2 * PI;
		p->player->pdx = cos(p->player->pa) * 5;
		p->player->pdy = sin(p->player->pa) * 5;
	}
	display(p);
	return (0);
}
