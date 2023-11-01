/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/31 13:13:46 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line_start;
	
	line_start = 
	if (!fd)
		return (NULL);
	else if (fd == 1)
		return get_from_output();
	else
		return get_from_file(fd);
		
	return (NULL);
}

#include <fcntl.h>

int main(void)
{
	char	c = 'A';
	int	fd = open("./text.txt", O_CREAT | O_RDWR, 0742);

	write(fd, &c, 1);
}