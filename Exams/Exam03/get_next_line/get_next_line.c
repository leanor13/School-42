
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 42

int	find_end_line_char(char *s)
{
	int	num;

	num = 0;
	if (!s)
		return (-1);
	while (s[num] && s[num] != '\n')
		num ++;
	if (s[num] == '\n')
		return (num);
	else
		return (-1);

}

char	*ft_strncpy(char *str, int n)
{
	char	*res;
	int		i = 0;

	res = malloc((n + 1) * sizeof(char));
	if (!str || n == 0)
		return (NULL);
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i ++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strlen(char *s)
{
	int len = 0;

	if (!s || !*s)
		return (0);
	while (s[len])
	{
		len ++;
	}
	return (len);
}

void	change_buff(char *buff, int end_line)
{
	int	i = 0;

	if (end_line < 0)
		return ;
	while (buff[end_line + i])
	{
		buff[i] = buff[end_line + i];
		i ++;
	}
	while (i < BUFFER_SIZE)
	{
		buff[i] = '\0';
		i ++;
	}
}

char	*get_next_line(int fd)
{
	static char buff[BUFFER_SIZE];
	char		*line;
	char		*result;
	int			end_line;

	line = NULL;
	if (buff[0])
	{
		end_line = find_end_line_char(buff);
		if (end_line >= 0)
		{
			line = ft_strncpy(buff, end_line);
			change_buff(buff, end_line);
			//printf("buff: %s", buff);
			return (line);
		}
	}
	while (read(fd, buff, BUFFER_SIZE))
	{
		end_line = find_end_line_char(buff);
		if (end_line >= 0)
		{
			line = ft_strncpy(buff, end_line);
			change_buff(buff, end_line);
			//printf("buff: %s", buff);
			return (line);
		}
	}
	if (*line=='\0')
		free(line);
	return (line);

}

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