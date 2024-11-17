#include "get_next_line.h"

char	*get_line(char *str)
{
	int	i;
	int	size;
	char	*line;

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
	if (str[i] && str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	size = ft_strlen(&str[i]) + 1;
	remain = malloc(sizeof(char) * size);
	if (!remain)
		return (NULL);
	while (str[i])
		remain[j++] = str[i++];
	remain[j] = '\0';
	free(str);
	return (remain);
}

int	nl_check(char *str)
{
	int	i;

	if (!str)
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
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (!nl_check(*buffer) && readed > 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			free(*buffer);
			return (0);
		}
		else if (readed > 0)
		{
			buff[readed] = '\0';
			*buffer = ft_strjoin(*buffer, buff);
			if (nl_check(*buffer))
				break;
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
	if (fd < 0)
		return (NULL);
	if (!read_file(fd, &buffer))
		return (NULL);
	if (buffer)
	{
		line = get_line(buffer);
		buffer = get_remain(buffer);
		if (!buffer)
			free(buffer);
	}
	return (line);
}
