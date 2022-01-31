
#include "../cub3d.h"

// need to find biggest column
int	map_height(char *filename)
{
	int		fd;
	int		count_height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count_height = 0;
	get_next_line(fd, &line);
	while (line != NULL)
	{
		count_height++;
		free(line);
		get_next_line(fd, &line);
	}
	close(fd);
	return (count_height);
}

// need to find longest row. Not all rows need to have the same length
int	map_width(char *filename, int res)
{
	int		count_width;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	res = 0;
	get_next_line(fd, &line);
	while (line && line[res] != '\0' && line[res] != '\n')
		res++;
	free(line);
	get_next_line(fd, &line);
	while (line != NULL)
	{
		count_width = 0;
		while (line[count_width] != '\0' && line[count_width] != '\n')
			count_width++;
		if (res != count_width)
			return (-1);
		free(line);
		get_next_line(fd, &line);
	}
	close(fd);
	return (res);
}

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
	exit(EXIT_FAILURE);
}
