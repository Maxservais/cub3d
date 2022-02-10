#include "../cub3d.h"

void	ft_error(int nb)
{
	if (nb < 14)
		write(1, "Error\n", 6);
	if (nb == FILENAME_ERROR)
	{
		write(1, "Usage: ./cub3d path_filename.cub\n", 33);
		write(1, "No more arguments are accepted\n", 31);
	}
	if (nb == FD_ER)
	{
		write(1, "Error opening the file\n", 23);
		write(1, "Please enter the path to a valid document.\n", 43);
	}
	if (nb == MALLOC_ER)
		write(1, "Error with a malloc\n", 20);
	else if (nb == FILE_ER)
		write(1, "The document doesn't respect the required syntax.\n", 50);
	else if (nb == END)
		write(1, "Thank you for playing\n", 22);
	exit(EXIT_FAILURE);
}

void	init_struct_fail(int message, int nb, t_param *param)
{
	if (nb > 0)
	{
		if (nb > 1)
		{
			if (nb > 2)
			{
				if (nb > 3)
				{
					if (nb > 4)
						free(param->txt);
					free(param->player);
				}
				free(param->key);
			}
			free(param->map->ceilling);
		}
		free(param->map->floor);
	}
	free(param->map);
	ft_error(message);
}

void	clear_the_lst(int message, t_list *lstmap, t_param *param)
{
	t_list	*tmp;

	while (lstmap)
	{
		tmp = lstmap;
		lstmap = lstmap->next;
		free(tmp->line);
		free(tmp);
	}
	init_struct_fail(message, MAX_STRUCT, param);
}

void	free_texture(t_list *lstmap, t_param *param, int message, int nb)
{
	if (param->map->no_texture)
		free(param->map->no_texture);
	if (param->map->so_texture)
		free(param->map->so_texture);
	if (param->map->we_texture)
		free(param->map->we_texture);
	if (param->map->ea_texture)
		free(param->map->ea_texture);
	if (nb > 0)
		clear_the_lst(message, lstmap, param);
	else
		init_struct_fail(message, MAX_STRUCT, param);
}

void	free_board(t_param *param, t_list *lstmap, int message)
{
	int	i;

	i = 0;
	while (i < param->map->height && param->map->board[i])
	{
		free(param->map->board[i]);
		i++;
	}
	free(param->map->board);
	if (!lstmap)
		free_texture(NULL, param, message, 0);
	free_texture(lstmap, param, message, 1);
}
