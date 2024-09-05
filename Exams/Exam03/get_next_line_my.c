#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	size_t len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (len + 1);
		len ++;
		str ++;
	}
	return (len);
}

char	*ft_str_join_line(char *s1, char *s2)
{
	char		*result;
	size_t		result_index;
	size_t		i=0;

	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result_index = 0;
	while (s1 && s1[i])
	{
		result[result_index] = s1[i];
		result_index ++;
		i ++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		result[result_index] = s2[i];
		result_index ++;
		if (s2[i] == '\n')
			break;
		i ++;
	}
	result[result_index] = '\0';
	free(s1);
	return (result);
}

size_t	clean_line(char	*buffer)
{
	size_t i=0;
	size_t j=0;
	int	found_new_line = 0;

	while (buffer[i])
	{
		if (found_new_line)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			found_new_line = 1;
		buffer[i] = '\0';
		i ++;
	}
	return (found_new_line);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE+1];
	char *line = NULL;
	char *temp;
	ssize_t bytes_read;

	if (fd<0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break;
			buffer[bytes_read] = '\0';
		}
		temp = ft_str_join_line(line, buffer);
		if (!temp)
			return (NULL);
		line = temp;
		if (clean_line(buffer))
			break;
	}

	if (line && line[0] == '\0' && bytes_read <=0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	// Открытие файла
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");  // Обработка ошибки открытия файла
		return 1;
	}

	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("line: %s\n", line);
			free(line);  // Освобождаем память, выделенную для line
		}
		else
			break;
	}

	close(fd);  // Закрытие файла
	return 0;
}