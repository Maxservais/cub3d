#include "../cub3d.h"

/*
key_up(), key_down(), key_left() and key_right() 
compute the new position of the player in the game.
*/

void	key_up(t_param *p)
{
	float	px;
	float	py;

	px = p->player->px;
	py = p->player->py;
	if (cos(p->player->pa) > 0
		&& p->map->board[(int)py][(int)(px + GAP)] != '1')
		p->player->px += cos(p->player->pa) * SPEED;
	else if (cos(p->player->pa) < 0
		&& p->map->board[(int)py][(int)(px - GAP)] != '1')
		p->player->px += cos(p->player->pa) * SPEED;
	if (sin(p->player->pa) > 0
		&& p->map->board[(int)(py + GAP)][(int)px] != '1')
		p->player->py += sin(p->player->pa) * SPEED;
	else if (sin(p->player->pa) < 0
		&& p->map->board[(int)(py - GAP)][(int)px] != '1')
		p->player->py += sin(p->player->pa) * SPEED;
}

void	key_down(t_param *p)
{
	float	px;
	float	py;

	px = p->player->px;
	py = p->player->py;
	if (cos(p->player->pa) > 0
		&& p->map->board[(int)py][(int)(px - GAP)] != '1')
		p->player->px -= cos(p->player->pa) * SPEED;
	else if (cos(p->player->pa) < 0
		&& p->map->board[(int)py][(int)(px + GAP)] != '1')
		p->player->px -= cos(p->player->pa) * SPEED;
	if (sin(p->player->pa) > 0
		&& p->map->board[(int)(py - GAP)][(int)px] != '1')
		p->player->py -= sin(p->player->pa) * SPEED;
	else if (sin(p->player->pa) < 0
		&& p->map->board[(int)(py + GAP)][(int)px] != '1')
		p->player->py -= sin(p->player->pa) * SPEED;
}

void	key_left(t_param *p)
{
	float	px;
	float	py;

	px = p->player->px;
	py = p->player->py;
	if (cos(p->player->pa + PI / 2) > 0
		&& p->map->board[(int)py][(int)(px - GAP)] != '1')
		p->player->px -= cos(p->player->pa + PI / 2) * SPEED;
	else if (cos(p->player->pa + PI / 2) < 0
		&& p->map->board[(int)py][(int)(px + GAP)] != '1')
		p->player->px -= cos(p->player->pa + PI / 2) * SPEED;
	if (sin(p->player->pa - PI / 2) > 0
		&& p->map->board[(int)(py + GAP)][(int)px] != '1')
		p->player->py -= sin(p->player->pa + PI / 2) * SPEED;
	else if (sin(p->player->pa - PI / 2) < 0
		&& p->map->board[(int)(py - GAP)][(int)px] != '1')
		p->player->py -= sin(p->player->pa + PI / 2) * SPEED;
}

void	key_right(t_param *p)
{
	float	px;
	float	py;

	px = p->player->px;
	py = p->player->py;
	if (cos(p->player->pa - PI / 2) > 0
		&& p->map->board[(int)py][(int)(px - GAP - PLAYER_OFFSET)] != '1')
		p->player->px += cos(p->player->pa + PI / 2) * SPEED;
	else if (cos(p->player->pa - PI / 2) < 0
		&& p->map->board[(int)py][(int)(px + GAP + PLAYER_OFFSET)] != '1')
		p->player->px += cos(p->player->pa + PI / 2) * SPEED;
	if (sin(p->player->pa + PI / 2) > 0
		&& p->map->board[(int)(py + GAP)][(int)px] != '1')
		p->player->py += sin(p->player->pa + PI / 2) * SPEED;
	else if (sin(p->player->pa + PI / 2) < 0
		&& p->map->board[(int)(py - GAP)][(int)px] != '1')
		p->player->py += sin(p->player->pa + PI / 2) * SPEED;
}
