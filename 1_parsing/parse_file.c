
#include "../cub3d.h"

/*
- Your program must take as a first argument a scene description file with the .cub extension.
- If any misconfiguration of any kind is encountered in the file, the program must exit properly and
return "Error\n" followed by an explicit error message of your choice.
*/

// Call parse_file from main function
// int	parse_file(t_param *param, char *filename)
// {

		// check all elements (e.g. NO ./path_to_the_north_texture)
		// check_elements(param, filename);

		// check map's content and fill board
		// check_map(param, filename);

// }

static t_list	*file_to_lst(char *filename)
{
	int	fd;
	int	ret;
	t_list	*new;
	t_list	*lstmap;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(FILE_ERROR);
	ret = 1;
	lstmap = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break;
		new = ft_lstnew(line);
		if (!new)
			ft_error(MALLOC_ER);
		ft_lstadd_back(&lstmap, new);
	}
	if (ret == -1)
		ft_error(FILE_ERROR);
	new = ft_lstnew(line);
	if (!new)
		ft_error(MALLOC_ER);
	ft_lstadd_back(&lstmap, new);
	close (fd);
	return (lstmap);
}

int		parse_file(t_param *param, char *filename)
{
	t_list	*lstmap;

	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		ft_error(FILENAME_ER);
	lstmap = file_to_lst(filename);
	check_content(param->map, lstmap);
	return (0);
}
