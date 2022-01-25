/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:54:14 by mservais          #+#    #+#             */
/*   Updated: 2022/01/25 10:08:40 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* 0. EXTERNAL LIBRARIES */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h> // A SUPPRIMER
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h" // is that necessary?
# include "mlx.h"

/* 1. MACROS */

# define ERROR_MSG "Error\nRelaunch the game please!\n"
# define BLOC_SIZE 30
# define ESCAPE 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define PI	3.14159265358

/* 2. CUSTOM STRUCTS */

typedef struct s_map
{
	int		width;
	int		height;
	char	**board;
}			t_map;

typedef struct s_player
{
	// int		img_width;
	// int		img_height;
	// void	*player;
	float	pdx;
	float	pdy;
	float	pa;
	float		px;
	float		py;
}			t_player;

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_addr;
    int			bits_per_pixel;
    int			line_length;
	int			endian;
	t_map		*map;
	t_player	*player;
}			t_param;

/* 3. MAIN FUNCTIONS */


/* 4. PARSER */
int	check_map(t_param *param, char *filename);
int	map_height(char *filename);
int	map_width(char *filename, int res);

/* 5. GAME DYNAMICS */

/* 5.0 Hooking into events */
int	close_win(t_param *param);
int	deal_key(int key, t_param *param);

/* Frame rendering */
void	my_mlx_pixel_put(t_param *param, int x, int y, int color);
void	draw_line(t_param *param, int x0, int y0, int x1, int y1);
void	draw_map2d(t_param *param);
void	draw_player(t_param *param);
void	erase_player(t_param *param);
void	display(t_param *p);

/* 6. MEMORY (DE)ALLOCATION */
int	init_structs(t_param *param);
int	init_board(t_param *p);
int	free_board(t_param *p, int n);

/* 7. UTILS */

#endif
