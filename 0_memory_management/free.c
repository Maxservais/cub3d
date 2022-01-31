
#include "../cub3d.h"

int	free_board(t_param *p, int n)
{
	while (n > 0)
	{
		free(p->map->board[n - 1]);
		n--;
	}
	free(p->map->board);
	return (1);
}
