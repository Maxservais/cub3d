#include "../cub3d.h"

static int	check_around(char **board, int i, int j, t_map *map)
{
	if (i == 0 || j == 0 || i == (map->height -1) || j == (map->width -1))
		return (0);
	if (board[i - 1][j] == ' ' || board[i + 1][j] == ' ' \
	|| board[i][j - 1] == ' ' || board[i][j + 1] == ' ')
		return (0);
	return (1);
}

void	check_map(t_param *param, char **board)
{
	int	i;
	int	j;

	i = -1;
	while (board[++i])
	{
		j = -1;
		while (board[i][++j])
		{
			if (board[i][j] == '0' && \
			(check_around(board, i, j, param->map) == 0))
				free_board(param, NULL, FILE_ER);
			else if (board[i][j] == 'N' || board[i][j] == 'E' \
			|| board[i][j] == 'S' || board[i][j] == 'W')
			{
				if (param->player->one == 1 || \
				(check_around(board, i, j, param->map) == 0))
					free_board(param, NULL, FILE_ER);
				param->player->one = 1;
			}
		}
	}
}
