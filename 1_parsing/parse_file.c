#include "../cub3d.h"

static int	open_the_fd(char *filename, int *ret, t_param *param)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		init_struct_fail(FD_ER, MAX_STRUCT, param);
	*ret = 1;
	return (fd);
}

static void	last_line(int ret, char *line, t_list *lstmap, t_param *param)
{
	t_list	*new;

	if (ret == -1)
		clear_the_lst(MALLOC_ER, lstmap, param);
	new = ft_lstnew(line);
	if (!new)
		clear_the_lst(MALLOC_ER, lstmap, param);
	ft_lstadd_back(&lstmap, new);
}

static t_list	*file_to_lst(char *filename, t_param *param)
{
	int		fd;
	int		ret;
	t_list	*new;
	t_list	*lstmap;
	char	*line;

	fd = open_the_fd(filename, &ret, param);
	lstmap = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret != 1)
			break ;
		new = ft_lstnew(line);
		if (!new)
		{
			close(fd);
			clear_the_lst(MALLOC_ER, lstmap, param);
		}
		ft_lstadd_back(&lstmap, new);
	}
	close (fd);
	last_line(ret, line, lstmap, param);
	return (lstmap);
}

void	parse_file(t_param *param, char *filename)
{
	t_list	*lstmap;

	if (ft_strncmp(&filename[ft_strlen(filename) - 4], ".cub", 4) != 0)
		ft_error(FILENAME_ERROR);
	lstmap = file_to_lst(filename, param);
	lstmap = check_content(param->map, lstmap, param);
	parse_map(param->map, lstmap, param);
}
