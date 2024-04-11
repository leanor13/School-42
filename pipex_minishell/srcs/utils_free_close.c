/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:02:16 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/11 10:58:19 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(int fd)
{
	if (fd != -1 && fd != STDERR_FILENO 
		&& fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}

void	close_all_protected(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i ++;
	}
}

void	close_all_unprotected(void)
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

