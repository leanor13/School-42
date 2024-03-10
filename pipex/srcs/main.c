/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/10 13:27:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_close(int fd, int reference)
{
	if (fd != reference)
	{
		dup2(fd, reference);
		close(fd);
	}
}

int	exec_command(t_command *command, int fd_in, int fd_out, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	else if (pid == 0)
	{
		dup_close(fd_in, STDIN_FILENO);
		dup_close(fd_out, STDOUT_FILENO);
		if (execve(command->path, command->args, envp) == -1)
		{
			perror("Execve error");
			exit (NEG_ERROR);
		}
	}
	else
	{
		close(fd_out);
		waitpid(pid, NULL, 0);
	}
	return (pid);
}

static void	close_both_ends(int fd[2], bool pipe_error)
{
	if (pipe_error)
		perror("Error creating pipe");
	close(fd[FD_IN]);
	close(fd[FD_OUT]);
}

int	exec_pipe(t_command *comm_list, int fd_files[2], int comm_num, char **envp)
{
	int	fd_pipe[2];
	int	fd[2];
	int	i;

	i = 0;
	fd[FD_IN] = fd_files[FD_IN];
	while (i <= comm_num - 1)
	{
		if (pipe(fd_pipe) == -1)
			return (close_both_ends(fd, PRINT_PIPE_ERROR), NEG_ERROR);
		if (i == comm_num - 1)
			fd[FD_OUT] = fd_files[FD_OUT];
		else
			fd[FD_OUT] = fd_pipe[FD_OUT];
		if (exec_command(&comm_list[i], fd[FD_IN], fd[FD_OUT], envp) < 0)
		{
			if (i != comm_num - 1)
				close(fd_files[FD_OUT]);
			return (close_both_ends(fd, !PRINT_PIPE_ERROR), NEG_ERROR);
		}
		close(fd[FD_IN]);
		fd[FD_IN] = fd_pipe[FD_IN];
		i ++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int			fd_files[2];
	t_command	*command_list;
	int			exec_pipe_result;

	fd_files[FD_IN] = open(av[1], O_RDONLY);
	if (fd_files[FD_IN] == -1)
		return (perror("Failed opening input file"), EXIT_FAILURE);
	fd_files[FD_OUT] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_files[FD_OUT] == -1)
	{
		close(fd_files[FD_IN]);
		return (perror("Failed opening output file"), EXIT_FAILURE);
	}
	command_list = build_command_list(ac, av, envp);
	if (!command_list)
		return (close_both_ends(fd_files, !PRINT_PIPE_ERROR), EXIT_FAILURE);
	exec_pipe_result = exec_pipe(command_list, fd_files, ac - 3, envp);
	free_command_list(command_list, ac - 3);
	if (exec_pipe_result == NEG_ERROR)
		return (EXIT_FAILURE);
	return (0);
}
