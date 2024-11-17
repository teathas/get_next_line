#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif


# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
int	ft_strlen(const char *s);
int	ft_strlcat(char *dst, const char *src, int size);
int	ft_strlcpy(char *dst, const char *src, int dstsize);

#endif
