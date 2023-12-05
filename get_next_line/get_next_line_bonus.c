/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2023/12/05 12:40:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FILE_NUM][BUFFER_SIZE + 1];
	char		*line;
	int			new_line;

	new_line = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= MAX_FILE_NUM)
	{
		if (fd > 0 && fd < MAX_FILE_NUM)
			ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		return (NULL);
	}
	while (new_line && (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE)))
	{
		line = ft_linejoin(line, buffer[fd]);
		ft_free(&new_line, buffer[fd]);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

/* void test_gnl(int fd, char *expected)
{
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line);
    }

    if (expected == NULL)
        printf("Expected: NULL\n");
    else
        printf("Expected: %s\n", expected);
} */

/* int main(int argc, char **argv)
{
    int fd;

    if (argc == 2)
    {
        // Read from file
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening file");
            return 1;
        }
    }
    else
    {
        // Read from standard input
        fd = 0;
    }

    test_gnl(fd, NULL);

    close(fd);

    return 0;
} */
