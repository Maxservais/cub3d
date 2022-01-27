
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

size_t	ft_strlen(char const *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_end_of_line(char *str);
size_t	ft_find_newline(char const *str);
char	*ft_return_null(char **line);
void	ft_cut(char str[], size_t n);
char	*ft_return(char buffer[], char **line, int byte_read);
char	*get_next_line(int fd);

#endif
