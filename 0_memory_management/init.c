/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:32:02 by mservais          #+#    #+#             */
/*   Updated: 2022/01/20 12:43:36 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		return (-1);
	param->player = malloc(sizeof(t_player));
	if (!param->player)
	{
		free(param->map);
		return (-1);
	}
	// param->player->px = BLOC_SIZE / 2 - 5; // starting position of player should be elsewhere!
	// param->player->py = BLOC_SIZE / 2 - 5;
	param->player->px = 300;
	param->player->py = 300;
	param->player->pa = 0;
	param->player->pdx = cos(param->player->pa) * 5;
	param->player->pdy = sin(param->player->pa) * 5;
	// param->sprite = malloc(sizeof(t_sprite));
	// if (!param->sprite)
	// {
	// 	free(param->player);
	// 	free(param->map);
	// 	return (-1);
	// }
	return (0);
}

int	init_board(t_param *p)
{
	int	row;

	p->map->board = malloc(sizeof(char *) * p->map->height);
	if (!p->map->board)
		return (-1);
	row = 0;
	while (row < p->map->height)
	{
		p->map->board[row] = malloc(sizeof(char) * p->map->width);
		if (!p->map->board[row])
			return (free_board(p, row));
		row++;
	}
	return (0);
}
