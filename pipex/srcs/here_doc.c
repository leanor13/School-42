/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:11:40 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/15 15:34:18 by yioffe           ###   ########.fr       */
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

void	here_doc(char *limiter, int *fd_files)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	exit_pipe_error(fd);
	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		exit (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		read_input(fd, limiter);
		free(fd_files);
		exit(EXIT_SUCCESS);
	}
	dup2(fd[0], STDIN_FILENO);
	close_both_ends(fd, !PRINT_PIPE_ERROR);
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
}

void	open_files_here_doc(int ac, char **av, int *fd_files)
{
	fd_files[FD_OUT] = open_file(ac, av, HERE_DOC);
	here_doc(av[2], fd_files);
	fd_files[FD_IN] = STDIN_FILENO;
}
