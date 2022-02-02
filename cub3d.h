
#ifndef CUB3D_H
# define CUB3D_H

/* 0. EXTERNAL LIBRARIES */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h> // A SUPPRIMER?
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"

/* 1. MACROS */

# define TRUE 1
# define FALSE 0
# define BLACK 0x000000
# define WHITE 0x00FFFFFF
# define CEILING 0x0087CEEB
# define FLOOR 0x00696969
# define PLAYER 0x000000FF
# define LINE 0x006A0DAD
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define GAP 0.6
# define PLAYER_OFFSET 0.25
# define FOV 60
# define SPEED 0.05
# define ESCAPE 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define PI	3.14159265358
# define P2	PI / 2
# define P3	3 * PI / 2
# define DR	0.0174533
# define PATH_TO_TEXTURE "textures/wall_dark_red.xpm" // temporary solution
# define ERROR_MSG "Error\nRelaunch the game please!\n"

/* 2. CUSTOM STRUCTS */

typedef struct s_map
{
	int		width;
	int		height;
	char	**board;
}			t_map;

typedef struct s_texture
{
	void	*img_ptr;
	char	*img_addr;
	int		width;
	int		height;
	int		bits_per_pixel;
    int		line_length;
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
	int		map_check_x;
	int		map_check_y;
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
	t_texture	*texture;
}			t_param;

/* 3. MAIN FUNCTIONS */

// add here necessary function's prototypes

/* 4. PARSER */
int		check_map(t_param *param, char *filename);
int		map_height(char *filename);
int		map_width(char *filename, int res);

/* 5. GAME DYNAMICS */

/* 5.0 Hooking into events */
int		close_win(t_param *param);
int		key_press(int key, t_param *p);
int		key_unpress(int key, t_param *p);
int		update_pos(t_param *p);

/* 5.1 Draw minimap */
void	draw_player(t_param *param);
void	draw_tile(t_param *param, int x, int y, int color);
void	draw_map2d(t_param *param);
void	draw_rays(t_param *p, t_ray *ray);
void	draw_minimap(t_param *p, t_ray *ray);

/* 5.2 Draw game 3D */
void	draw_vert_line(t_param *p, t_ray *ray, int i);
void	draw_walls(t_param *p, t_ray *ray);
int		display(void *param);

/* 5.3 Raycasting */
float	len_ray(t_param *param, t_ray *ray, float angle);

/* 5.4 Utils */
void	my_mlx_pixel_put(t_param *param, int x, int y, int color);
int		get_color(t_texture *text, int x, int y);
void	draw_line(t_param *param, int x0, int y0, int x1, int y1);

/* 6. MEMORY (DE)ALLOCATION */
int		init_structs(t_param *param);
int		init_board(t_param *p);
int		load_textures(t_param *p);
int		free_board(t_param *p, int n);

/* 7. UTILS */

// add here necessary function's prototypes

#endif
