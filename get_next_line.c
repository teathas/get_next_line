#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int	i;
	int	size;
	char	*line;

	size = 0;
	if (*str == '\0')
		return (NULL);
	while (str[size] && str[size] != '\n')
		size++;
	if (str[size] == '\n')
		size++;
	line = malloc(size + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_remain(char	*str)
{
	int	i;
	int	j;
	char	*remain;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	remain = malloc(ft_strlen(&str[i]) + 1);
	if (!remain)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	free(str);
	str = NULL;
	return (remain);
}

int	nl_check(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	read_file(int fd, char **buffer)
{
	char	*buff;
	int	readed;

	readed = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (0);
	while (!nl_check(*buffer) && readed > 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			free(*buffer);
			*buffer = NULL;
			return (0);
		}
		else if (readed > 0)
		{
			buff[readed] = '\0';
			*buffer = ft_strjoin(*buffer, buff);
			if (*buffer == NULL)
			{
				free(buff);
				return (0);
			}
		}
	}
	free(buff);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	line = NULL;
	if (fd < 0)
		return (NULL);
	if (!read_file(fd, &buffer))
		return (NULL);
	if (buffer != NULL)
	{
		line = ft_get_line(buffer);
		buffer = ft_get_remain(buffer);
		if (!buffer)
			free(buffer);
	}
	return (line);
}
