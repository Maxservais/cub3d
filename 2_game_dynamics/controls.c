#include "../cub3d.h"

/*
close_win() closes the window whenever the player presses the ESC key 
or clicks on the red-cross of the window.
*/

int	close_win(t_param *param)
{
	// free everything

	// destroy window & exit
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	exit(0);
}

/*
key_press() records which key was pressed by the player.
*/

int	key_press(int key, t_param *p)
{
	if (key == ESCAPE)
		close_win(p);
	if (key == UP)
		p->key->key_up = 1;
	else if (key == DOWN)
		p->key->key_down = 1;
	else if (key == LEFT)
		p->key->key_left = 1;
	else if (key == RIGHT)
		p->key->key_right = 1;
	else if (key == LEFT_ARROW)
		p->key->key_arrow_left = 1;
	else if (key == RIGHT_ARROW)
		p->key->key_arrow_right = 1;
	return (0);
}

/*
key_unpress() records which key was unpressed by the player.
*/

int	key_unpress(int key, t_param *p)
{
	if (key == UP)
		p->key->key_up = 0;
	else if (key == DOWN)
		p->key->key_down = 0;
	else if (key == LEFT)
		p->key->key_left = 0;
	else if (key == RIGHT)
		p->key->key_right = 0;
	else if (key == LEFT_ARROW)
		p->key->key_arrow_left = 0;
	else if (key == RIGHT_ARROW)
		p->key->key_arrow_right = 0;
	return (0);
}

/*
update_pos() updates the position of the player in the game.
*/

int	update_pos(t_param *p)
{
	// int		x0;
	// int		y0;
	// int		ipx;
	// int		ipy;

	// x0 = 0;
	// if (p->player->pdx < 0)
	// 	x0 = -20;
	// else
	// 	x0 = 20;
	// y0 = 0;
	// if (p->player->pdy < 0)
	// 	y0 = -20;
	// else
	// 	y0 = 20;
	// ipx = p->player->px;
	// int ipx_add_xo = (p->player->px + x0);
	// int	ipx_sub_xo = (p->player->px - x0);
	// ipy = p->player->py;
	// int ipx_add_yo = (p->player->py + y0);
	// int	ipx_sub_yo = (p->player->py - y0);
	if (p->key->key_up)
	{
		if (p->map->board[(int)p->player->py][(int)(p->player->px + p->player->pdx + GAP)] != '1')
			p->player->px += p->player->pdx;
		if (p->map->board[(int)(p->player->py + p->player->pdy + GAP)][(int)p->player->px] != '1')
			p->player->py += p->player->pdy;
	}
	if (p->key->key_down)
	{
		if (p->map->board[(int)p->player->py][(int)(p->player->px - p->player->pdx - GAP)] != '1')
			p->player->px -= p->player->pdx;
		if (p->map->board[(int)(p->player->py - p->player->pdy - GAP)][(int)p->player->px] != '1')
			p->player->py -= p->player->pdy;
	}
	if (p->key->key_left)
	{
		if (p->map->board[(int)p->player->py][(int)(p->player->px - cos(p->player->pa + PI / 2) * SPEED - GAP)] != '1')
			p->player->px -= cos(p->player->pa + PI / 2) * SPEED;
		if (p->map->board[(int)(p->player->py - sin(p->player->pa + PI / 2) * SPEED - GAP)][(int)p->player->px] != '1')
			p->player->py -= sin(p->player->pa + PI / 2) * SPEED;
	}
	if (p->key->key_right)
	{
		if (p->map->board[(int)p->player->py][(int)(p->player->px + cos(p->player->pa + PI / 2) * SPEED + GAP)] != '1')
			p->player->px += cos(p->player->pa + PI / 2) * SPEED;
		if (p->map->board[(int)(p->player->py + sin(p->player->pa + PI / 2) * SPEED + GAP)][(int)p->player->px] != '1')
			p->player->py += sin(p->player->pa + PI / 2) * SPEED;
	}
	if (p->key->key_arrow_left)
	{
		p->player->pa -= SPEED;
		if (p->player->pa < 0)
			p->player->pa += 2 * PI;
		p->player->pdx = cos(p->player->pa) * SPEED;
		p->player->pdy = sin(p->player->pa) * SPEED;
	}
	if (p->key->key_arrow_right)
	{
		p->player->pa += SPEED;
		if (p->player->pa > 2 * PI)
			p->player->pa -= 2 * PI;
		p->player->pdx = cos(p->player->pa) * SPEED;
		p->player->pdy = sin(p->player->pa) * SPEED;
	}
	return (0);
}


// void    key_move(float valcos, float valsin, t_cub *cub)
// {
//     if (sin(valsin) < 0 && cub->map[(int)(cub->player.y - HITBOX)][(int)cub->player.x] != '1')
//         cub->player.y += sin(valsin) * SPEED;
//     else if (sin(valsin) > 0 && cub->map[(int)(cub->player.y + HITBOX)][(int)cub->player.x] != '1')
//         cub->player.y += sin(valsin) * SPEED;
//     if (cos(valcos) > 0 && cub->map[(int)cub->player.y][(int)(cub->player.x + HITBOX)] != '1')
//         cub->player.x += cos(valcos) * SPEED;
//     else if (cos(valcos) < 0 && cub->map[(int)cub->player.y][(int)(cub->player.x - HITBOX)] != '1')
//         cub->player.x += cos(valcos) * SPEED;
// }

// void    move_manager(t_cub *cub)
// {
//     if (cub->key.w == 1)
//         key_move(cub->player.angle, cub->player.angle * -1, cub);
//     if (cub->key.s == 1)
//         key_move(cub->player.angle + PI, cub->player.angle, cub);
//     if (cub->key.a == 1)
//         key_move(cub->player.angle + MIDPI, cub->player.angle - MIDPI, cub);
//     if (cub->key.d == 1)
//         key_move(cub->player.angle - MIDPI, cub->player.angle + MIDPI, cub);
// }