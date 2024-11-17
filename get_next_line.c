#include "get_next_line.h"

char	*get_line(char *str)
{
	int	i;
	int	size;
	char	*line;

	if (!str)
		return (NULL);
	i = 0;
	size = 0;
	while (str[i] && str[i] != '\n')
	{
		i++;
		size++;
	}
	line = malloc((size + 2) * sizeof(char));
	if (!line)
		return (line);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

char	*get_remain(char	*str)
{
	int	i;
	int	j;
	int	size;
	char	*remain;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	size = ft_strlen(&str[i]) + 1;
	remain = malloc(sizeof(char) * size);
	if (!remain)
		return (NULL);
	while (str[i])
		remain[j++] = str[i++];
	free(str);
	remain[j] = '\0';
	return (remain);
}

int	read_file(int fd, char **buffer)
{
	char	*buff;
	int	readed;

	readed = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (readed > 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			return (0);
		}
		if (readed > 0)
		{
			buff[readed] = '\0';
			*buffer = ft_strjoin(*buffer, buff);
		}
	}
	free(buff);
	return (1);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffer;

	line = NULL;
	if (!read_file(fd, &buffer))
		return (NULL);
	line = get_line(buffer);
	buffer = get_remain(buffer);
	return (line);
}
