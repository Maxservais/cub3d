/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:26:06 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 19:15:53 by mservais         ###   ########.fr       */
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
		p->player->y -= 10;
	else if (key == DOWN /*&& !try_move(p, p->player->x, p->player->y + 1, 0)*/)
		p->player->y += 10;
	else if (key == LEFT /*&& !try_move(p, p->player->x - 1, p->player->y, 0)*/)
		p->player->x -= 10;
	else if (key == RIGHT /*&& !try_move(p, p->player->x + 1, p->player->y, 0)*/)
		p->player->x += 10;
	display(p);
	return (0);
}
