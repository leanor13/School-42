/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/11 11:01:39 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	exec_command(t_command *command, int *fd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	else if (pid == 0)
	{
		dup_close(fd[FD_IN], STDIN_FILENO);
		dup_close(fd[FD_OUT], STDOUT_FILENO);
		if (execve(command->path, command->args, envp) == -1)
		{
			perror("Execve error");
			exit (NEG_ERROR);
		}
	}
	else
		close_both_ends(fd, !PRINT_PIPE_ERROR);
	return (pid);
}

static int	exec_pipe(t_command *c_list, int fd_files[2], int len, char **envp)
{
	int	fd_pipe[2];
	int	fd[2];
	int	i;
	int	status;

	i = 0;
	fd[FD_IN] = fd_files[FD_IN];
	while (i <= len - 1)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Error creating pipe");
			return (close_all_protected(), NEG_ERROR);
		}
		if (i == len - 1)
			fd[FD_OUT] = fd_files[FD_OUT];
		else
			fd[FD_OUT] = fd_pipe[FD_OUT];
		if (exec_command(&c_list[i], fd, envp) < 0)
			return (close_all_protected(), NEG_ERROR);
		ft_close(fd[FD_IN]);
		fd[FD_IN] = fd_pipe[FD_IN];
		ft_close(fd_pipe[FD_OUT]);
		i ++;
	}
	ft_close(fd_pipe[FD_IN]);
	ft_close(fd[FD_OUT]);
	for (i = 0; i < len; i ++)
		waitpid(-1, &status, 0);
	return (status);
}

int	open_file(int ac, char **av, int type)
{
	int	fd;

	fd = 0;
	if (type == HERE_DOC)
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUTPUT_FILE)
		fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INPUT_FILE)
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		if (type == INPUT_FILE)
			perror("Failed opening input file");
		else
			perror("Failed opening output file");
		return (NEG_ERROR);
	}
	return (fd);
}

int	*handle_input(int ac, char **av)
{
	int	*fd_files;

	fd_files = malloc(sizeof(int) * 2);
	if (!fd_files)
	{
		perror("Failed to allocate memory for fd_files");
		exit (EXIT_FAILURE);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
		open_files_here_doc(ac, av, fd_files);
	else
	{
		fd_files[FD_IN] = open_file(ac, av, INPUT_FILE);
		fd_files[FD_OUT] = open_file(ac, av, OUTPUT_FILE);
	}
	if (fd_files[FD_OUT] < 0 || fd_files[FD_IN] < 0)
	{
		close_all_protected();
		free(fd_files);
		exit (EXIT_FAILURE);
	}
	return (fd_files);
}

int	main(int ac, char **av, char **envp)
{
	int			*fd_files;
	t_command	*command_list;
	int			status;

	validate_params(ac, av);
	fd_files = handle_input(ac, av);
	if ((ft_strcmp(av[1], "here_doc") == 0) && (ac--))
		av ++;
	command_list = build_command_list(ac, av, envp);
	if (!command_list)
	{
		close_all_protected();
		return (free(fd_files), EXIT_FAILURE);
	}
	status = exec_pipe(command_list, fd_files, ac - 3, envp);
	close_all_protected();
	free(fd_files);
	free_command_list(command_list, ac - 3);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
