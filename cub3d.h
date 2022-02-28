#ifndef CUB3D_H
# define CUB3D_H

/* 0. EXTERNAL LIBRARIES */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

/* 1. MACROS */

# define FALSE 0
# define TRUE 1
# define WEST 0
# define EAST 1
# define NORTH 2
# define SOUTH 3
# define BLACK 0x000000
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define GAP 0.6
# define PLAYER_OFFSET 0.25
# define FOV 60
# define SPEED 0.05
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESCAPE 53
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define PI	3.14159265358
# define DR	0.0174533

/* 1.1 MACROS ERROR */

# define MAX_STRUCT 5
# define FILENAME_ERROR 10
# define MALLOC_ER 11
# define FD_ER 12
# define FILE_ER 13
# define END 14

/* 2. CUSTOM STRUCTS */

typedef struct s_map
{
	int		width;
	int		height;
	char	**board;
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
	int		*floor;
	int		*ceilling;
}			t_map;

typedef struct s_texture
{
	void	*img_ptr;
	char	*img_addr;
	int		width;
	int		height;
	int		bpp;
	int		l_len;
	int		endian;
}			t_texture;

typedef struct s_key
{
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		key_arrow_left;
	int		key_arrow_right;
}			t_key;

typedef struct s_player
{
	int		one;
	float	pdx;
	float	pdy;
	float	pa;
	float	px;
	float	py;
}			t_player;

typedef struct s_ray
{
	float	start_x;
	float	start_y;
	float	dir_x;
	float	dir_y;
	float	step_size_x;
	float	step_size_y;
	float	distance;
	float	intersect_x;
	float	intersect_y;
	float	length_x;
	float	length_y;
	float	line_height;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		collision_detected;
	int		vertical;
}			t_ray;

typedef struct s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			tile_size;
	t_map		*map;
	t_key		*key;
	t_player	*player;
	t_texture	*txt;
}			t_param;

/* 3. PARSER */
void				parse_file(t_param *param, char *filename);
t_list				*check_content(t_map *map, t_list *lstmap, t_param *param);
void				parse_map(t_map *map, t_list *lstmap, t_param *param);
void				check_map(t_param *param, char **board);
int					pass_the_f_or_c(char *line, t_list *lstmap, t_param *param);

/* 4. GAME DYNAMICS */

/* 4.0 Hooking into events */
int					close_win(t_param *param);
int					key_press(int key, t_param *p);
int					key_unpress(int key, t_param *p);
int					update_pos(t_param *p);
void				key_up(t_param *p);
void				key_down(t_param *p);
void				key_left(t_param *p);
void				key_right(t_param *p);

/* 4.1 Draw minimap */
void				draw_minimap(t_param *p, t_ray *ray);

/* 4.2 Draw game 3D */
int					display(void *param);

/* 4.3 Raycasting */
float				len_ray(t_param *param, t_ray *ray, float angle);

/* 4.4 Utils */
void				my_mlx_pixel_put(t_param *param, int x, int y, int color);
int					get_color(t_texture *text, int x, int y);
unsigned long long	rgb_to_hex(int r, int g, int b);
// void				draw_line(t_param *param, int x0, int y0, int x1, int y1);

/* 5. MEMORY (DE)ALLOCATION */
void				init_structs(t_param *param);
void				init_board(char **board, int nb);
int					load_textures(t_param *p, int i);
void				initialize_player_pos(t_param *p, int row, int col);
void				init_struct_fail(int message, int nb, t_param *param);
void				ft_error(int nb);
void				clear_the_lst(int message, t_list *lstmap, t_param *param);
void				free_texture(t_list *lst, t_param *param, int m, int nb);
void				free_board(t_param *param, t_list *lstmap, int message);

#endif
