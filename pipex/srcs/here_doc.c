/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/14 15:05:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	read_input(int fd[2], char *limiter)
{
	char	*line;

	ft_close(fd[0]);
	while (true)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			perror("Error reading from standard input");
			exit(EXIT_FAILURE);
		}
		if (strncmp(line, limiter, strlen(limiter)) == 0
			&& strlen(line) == strlen(limiter) + 1)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	ft_close(fd[1]);
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		read_input(fd, limiter);
		exit(EXIT_SUCCESS);
	}
	dup2(fd[0], STDIN_FILENO);
	close_both_ends(fd, !PRINT_PIPE_ERROR);
	wait(NULL);
}
