/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:32:02 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 17:45:47 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_structs(t_param *param)
{
	param->map = malloc(sizeof(t_map));
	if (!param->map)
		return (-1);
	// param->player = malloc(sizeof(t_player));
	// if (!param->player)
	// {
	// 	free(param->map);
	// 	return (-1);
	// }
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
