#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
	{
		if (s[len] == '\n')
			return (len + 1);
		len ++;
	}
	return (len);
}

char *ft_str_join(char *s1, char *s2)
{
	char	*result;
	int		res_index = 0;
	int		i;

	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
	{
		free(s1);
		return(NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		result[res_index] = s1[i];
		res_index ++;
		i ++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		result[res_index] = s2[i];
		res_index ++;
		if (s2[i] == '\n')
			break;
		i ++;
	}
	result[res_index] = '\0';
	free(s1);
	return (result);
	
}

int	clear_buff(char *str)
{
	int	found_new_line = 0;
	int	i=0;
	int	j=0;

	while (str[i])
	{
		if (found_new_line)
		{
			str[j] = str[i];
			j ++;
		}
		if (str[i] == '\n')
		{
			found_new_line = 1;
		}
		str[i] = '\0';
		i ++;
	}
	return (found_new_line);
}


char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char	*line = NULL;
	char	*temp;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
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
		temp = ft_str_join(line, buffer);
		if (!temp)
			return (NULL);
		line = temp;
		if (clear_buff(buffer))
			break;
	}

	if (line && line[0] == '\0' && bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			return (0);
// 		printf("line: %s", line);
// 	}
// 	close(fd);
// }

int main(void)
{
	int	fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("1: %s", line);
	free(line);
	line = get_next_line(fd);
	printf("2: %s", line);
	free(line);
	return (0);
}