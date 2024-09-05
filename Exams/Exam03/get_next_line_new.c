#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the length of a string, stopping at '\n' if present
size_t	ft_strlen(char *s)
{
	size_t	len = 0;

	if (!s)
		return (0);
	while (s[len])
	{
		if (s[len] == '\n')
			return (len + 1);
		len++;
	}
	return (len);
}

// Function to join two strings, stopping at the first '\n' in the second string
char	*strjoin_line(char *s1, char *s2)
{
	char	*s3;
	size_t	i = 0, j = 0;

	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1 && s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		s3[j++] = s2[i];
		if (s2[i++] == '\n')
			break ;
	}
	s3[j] = '\0';
	free(s1);
	return (s3);
}

// Function to clean the buffer, removing processed data and shifting remaining data
size_t	clean_line(char *buffer)
{
	size_t	i = 0, j = 0;
	int		found_newline = 0;

	printf("\nbuffer before clean: %s\n", buffer);
	while (buffer[i])
	{
		if (found_newline)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			found_newline = 1;
		buffer[i++] = '\0';
	}
	printf("\nbuffer after clean: %s\n", buffer);
	return (found_newline);
}

// Function to read the next line from a file descriptor
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line = NULL;
	char		*temp;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buffer[bytes_read] = '\0';
		}

		temp = strjoin_line(line, buffer);
		if (!temp)
			return (NULL);
		line = temp;

		if (clean_line(buffer))
			break ;
	}

	if (line && line[0] == '\0' && bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

// Test main function to demonstrate the get_next_line function
int main() {
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) 
    {
        perror("Error opening file");
        return 1;
    }
    // while ((line = get_next_line(fd)) != NULL) 
    // {
    //     printf("Read line: %s\n", line);
    //     free(line);
    // }
	line = get_next_line(fd);
	printf("line: %s", line);
    close(fd);
    return 0;
}
