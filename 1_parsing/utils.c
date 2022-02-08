#include "../cub3d.h"

void	ft_error(int nb)
{
	if (nb == FILE_ERROR)
		write(1, "Error with the file\n", 20);
	if (nb == MALLOC_ER)
		write(1, "Error Malloc\n", 13);
	else if (nb == ELEMENT_ER)
		write(1, "Error with one or more element\n", 31);
	else if (nb == FILENAME_ER)
		write(1, "Error with the ame of the file, it's not a .cub\n", 48);
	else if (nb == COLOR_ER)
		write(1, "Error with the color in the file .cub\n", 38);
	exit(EXIT_FAILURE);
}
