/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:02:16 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/15 15:47:29 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	free_command_list(t_command *command_list, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (command_list[i].args[j])
		{
			free(command_list[i].args[j]);
			command_list[i].args[j] = NULL;
			j++;
		}
		free(command_list[i].args);
		command_list[i].args = NULL;
		free(command_list[i].path);
		command_list[i].path = NULL;
		i++;
	}
	free(command_list);
	command_list = NULL;
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

void	dup_close(int fd, int reference)
{
	if (fd != reference)
	{
		dup2(fd, reference);
		ft_close(fd);
	}
}
