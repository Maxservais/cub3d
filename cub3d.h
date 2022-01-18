/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:54:14 by mservais          #+#    #+#             */
/*   Updated: 2022/01/18 17:44:24 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* 0. EXTERNAL LIBRARIES */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h" // is that necessary?
# include "mlx.h"

/* 1. MACROS */

# define ERROR_MSG "Error\nRelaunch the game please!\n"
# define ESCAPE 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

/* 2. CUSTOM STRUCTS */

typedef struct s_map
{
	int		width;
	int		height;
	char	**board;
}			t_map;

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
}			t_param;

/* 3. MAIN FUNCTIONS */


/* 4. PARSER */
int	check_map(t_param *param, char *filename);
int	map_height(char *filename);
int	map_width(char *filename, int res);




/* 5. CONTROL FLOW */
int	close_win(t_param *param);
int	deal_key(int key, t_param *param);

/* 6. MEMORY (DE)ALLOCATION */
int	init_structs(t_param *param);
int	init_board(t_param *p);
int	free_board(t_param *p, int n);

/* 7. UTILS */

#endif
