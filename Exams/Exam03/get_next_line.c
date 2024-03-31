
#include <stdlib.h>
#include <fcntl.h>

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

	res = malloc((n + 1) * sizeof(char));
	if (!str || n == 0)
		return (NULL);
	while (*str && n > 0)
	{
		*res = *str;
		n --;
	}
	*res = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char *buff[BUFFER_SIZE];
	char		*line;
	char		*result;
	int			end_line;

	while (read(fd, buff, BUFFER_SIZE))
	{
		end_line = find_end_line_char(buff);
		if (end_line >= 0)
			line = 	
	}

}

int main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
}