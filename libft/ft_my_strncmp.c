#include "libft.h"

int	ft_my_strncmp(char *s1, char *s2, unsigned int nb)
{
	while (*s1 && ft_is_wspace(*s1))
		s1++;
	while (1)
	{
		if ((!*s1 && !*s2) || !nb)
			return (0);
		if (*s1 == *s2)
		{
			s1++;
			s2++;
			nb--;
		}
		else
			return ((int)((unsigned char)(*s1) - (unsigned char)(*s2)));
	}
}
