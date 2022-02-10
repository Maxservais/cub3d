#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32

# endif

int		get_next_line(int fd, char **line);
int		is_in_str(char *str, char c);
char	*ft_strdup_until(char *src, char c);
char	*ft_strdup_from(char *src, int from);
size_t	ft_strlen_until(char *str, char c);

#endif
