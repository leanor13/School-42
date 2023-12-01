/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2023/12/01 11:57:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			nl_finder;

	nl_finder = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	while (nl_finder && (buffer[0] || read(fd, buffer, BUFFER_SIZE)))
	{
		line = ft_strjoin(line, buffer);
		ft_free(&nl_finder, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

/* int main(int argc, char **argv) {
    int fd;
    char *line;

    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("Error opening file");
            return 1;
        }
    } else {
        // If no file provided, read from standard input
        fd = 0;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);

    return 0;
} */
