/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:02:16 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/24 13:47:32 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(int fd)
{
	if (fd != -1 && fd != STDERR_FILENO 
		&& fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}

void	ft_close_protected(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i ++;
	}
}

void	ft_close_all(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i ++;
	}
}

void	close_both_ends(int fd[2], bool pipe_error)
{
	if (pipe_error)
		perror("Error creating pipe");
	ft_close(fd[FD_IN]);
	ft_close(fd[FD_OUT]);
}

void	close_3_fds(int fd_files[2], int fd[2], int fd_pipe[2])
{
	close_both_ends(fd_files, !PRINT_PIPE_ERROR);
	close_both_ends(fd, !PRINT_PIPE_ERROR);
	close_both_ends(fd_pipe, !PRINT_PIPE_ERROR);
}
