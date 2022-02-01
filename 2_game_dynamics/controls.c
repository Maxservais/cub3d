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
key_unpress() records when a key that was pressed is released by the player.
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
	if (p->key->key_up)
	{
		if (cos(p->player->pa) > 0 && p->map->board[(int)p->player->py][(int)(p->player->px + GAP)] != '1')
			p->player->px += cos(p->player->pa) * SPEED;
		else if (cos(p->player->pa) < 0 && p->map->board[(int)p->player->py][(int)(p->player->px - GAP)] != '1')
			p->player->px += cos(p->player->pa) * SPEED;
		if (sin(p->player->pa) > 0 && p->map->board[(int)(p->player->py + GAP)][(int)p->player->px] != '1')
			p->player->py += sin(p->player->pa) * SPEED;
		else if (sin(p->player->pa) < 0 && p->map->board[(int)(p->player->py - GAP)][(int)p->player->px] != '1')
			p->player->py += sin(p->player->pa) * SPEED;
	}
	if (p->key->key_down)
	{
		if (cos(p->player->pa) > 0 && p->map->board[(int)p->player->py][(int)(p->player->px - GAP)] != '1')
			p->player->px -= cos(p->player->pa) * SPEED;
		else if (cos(p->player->pa) < 0 && p->map->board[(int)p->player->py][(int)(p->player->px + GAP)] != '1')
			p->player->px -= cos(p->player->pa) * SPEED;
		if (sin(p->player->pa) > 0 && p->map->board[(int)(p->player->py - GAP)][(int)p->player->px] != '1')
			p->player->py -= sin(p->player->pa) * SPEED;
		else if (sin(p->player->pa) < 0 && p->map->board[(int)(p->player->py + GAP)][(int)p->player->px] != '1')
			p->player->py -= sin(p->player->pa) * SPEED;
	}
	if (p->key->key_left)
	{
		if (cos(p->player->pa + PI / 2) > 0 && p->map->board[(int)p->player->py][(int)(p->player->px - GAP)] != '1')
			p->player->px -= cos(p->player->pa + PI / 2) * SPEED;
		else if (cos(p->player->pa + PI / 2) < 0 && p->map->board[(int)p->player->py][(int)(p->player->px + GAP)] != '1')
			p->player->px -= cos(p->player->pa + PI / 2) * SPEED;
		if (sin(p->player->pa - PI / 2) > 0 && p->map->board[(int)(p->player->py + GAP)][(int)p->player->px] != '1')
			p->player->py -= sin(p->player->pa + PI / 2) * SPEED;
		else if (sin(p->player->pa - PI / 2) < 0 && p->map->board[(int)(p->player->py - GAP)][(int)p->player->px] != '1')
			p->player->py -= sin(p->player->pa + PI / 2) * SPEED;
	}
	if (p->key->key_right)
	{
		if (cos(p->player->pa - PI / 2) > 0 && p->map->board[(int)p->player->py][(int)(p->player->px - GAP)] != '1')
			p->player->px += cos(p->player->pa + PI / 2) * SPEED;
		else if (cos(p->player->pa - PI / 2) < 0 && p->map->board[(int)p->player->py][(int)(p->player->px + GAP)] != '1')
			p->player->px += cos(p->player->pa + PI / 2) * SPEED;
		if (sin(p->player->pa + PI / 2) > 0 && p->map->board[(int)(p->player->py + GAP)][(int)p->player->px] != '1')
			p->player->py += sin(p->player->pa + PI / 2) * SPEED;
		else if (sin(p->player->pa + PI / 2) < 0 && p->map->board[(int)(p->player->py - GAP)][(int)p->player->px] != '1')
			p->player->py += sin(p->player->pa + PI / 2) * SPEED;
	}
	if (p->key->key_arrow_left)
	{
		p->player->pa -= SPEED;
		if (p->player->pa < 0)
			p->player->pa += 2 * PI;
	}
	if (p->key->key_arrow_right)
	{
		p->player->pa += SPEED;
		if (p->player->pa > 2 * PI)
			p->player->pa -= 2 * PI;
	}
	return (0);
}
