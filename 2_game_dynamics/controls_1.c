#include "../cub3d.h"

/*
close_win() closes the window whenever the player presses the ESC key 
or clicks on the red-cross of the window.
*/

int	close_win(t_param *param)
{
	free_all(param);
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
	if (p->key->key_up == 1)
		key_up(p);
	if (p->key->key_down == 1)
		key_down(p);
	if (p->key->key_left == 1)
		key_left(p);
	if (p->key->key_right == 1)
		key_right(p);
	if (p->key->key_arrow_left == 1)
	{
		p->player->pa -= SPEED;
		if (p->player->pa < 0)
			p->player->pa += 2 * PI;
	}
	if (p->key->key_arrow_right == 1)
	{
		p->player->pa += SPEED;
		if (p->player->pa > 2 * PI)
			p->player->pa -= 2 * PI;
	}
	return (0);
}
