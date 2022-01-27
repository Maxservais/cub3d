
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		count_height++;
		free(line);
		line = get_next_line(fd);
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
	line = get_next_line(fd);
	while (line && line[res] != '\0' && line[res] != '\n')
		res++;
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count_width = 0;
		while (line[count_width] != '\0' && line[count_width] != '\n')
			count_width++;
		if (res != count_width)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (res);
}
