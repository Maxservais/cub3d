#include "../cub3d.h"

static int	open_the_fd(char *filename, int *ret)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error(FILE_ERROR);
	*ret = 1;
	return (fd);
}

static void	last_line(int ret, char *line, t_list *lstmap)
{
	t_list	*new;

	if (ret == -1)
		ft_error(FILE_ERROR);
	new = ft_lstnew(line);
	if (!new)
		ft_error(MALLOC_ER);
	ft_lstadd_back(&lstmap, new);
}

static t_list	*file_to_lst(char *filename)
{
	int		fd;
	int		ret;
	t_list	*new;
	t_list	*lstmap;
	char	*line;

	fd = open_the_fd(filename, &ret);
	lstmap = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break ;
		new = ft_lstnew(line);
		if (!new)
			ft_error(MALLOC_ER);
		ft_lstadd_back(&lstmap, new);
	}
	last_line(ret, line, lstmap);
	close (fd);
	return (lstmap);
}

int	parse_file(t_param *param, char *filename)
{
	t_list	*lstmap;

	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		ft_error(FILENAME_ER);
	lstmap = file_to_lst(filename);
	lstmap = check_content(param->map, lstmap);
	parse_map(param->map, lstmap, param);
	return (0);
}
