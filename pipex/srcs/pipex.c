/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/12 20:00:51 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	dup_close(int fd, int reference)
{
	if (fd != reference)
	{
		dup2(fd, reference);
		close(fd);
	}
}

static int	exec_command(t_command *command, int fd_in, int fd_out, char **envp)
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
		close(fd_in);
        close(fd_out);
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

static int	exec_pipe(t_command *c_list, int fd_files[2], int len, char **envp)
{
	int	fd_pipe[2];
	int	fd[2];
	int	i;
	pid_t *pids;

	i = 0;
	pids = malloc(sizeof(pid_t)*len);
	fd[FD_IN] = fd_files[FD_IN];
	while (i <= len - 1)
	{
		if (pipe(fd_pipe) == -1)
			return (close_both_ends(fd, PRINT_PIPE_ERROR), NEG_ERROR);
		if (i == len - 1)
			fd[FD_OUT] = fd_files[FD_OUT];
		else
			fd[FD_OUT] = fd_pipe[FD_OUT];
		pids[i] = exec_command(&c_list[i], fd[FD_IN], fd[FD_OUT], envp);
		if (pids[i] < 0)
		{
			if (i != len - 1)
				close(fd_files[FD_OUT]);
			close_both_ends(fd_pipe, !PRINT_PIPE_ERROR);
			free(pids);
			return (close_both_ends(fd, !PRINT_PIPE_ERROR), NEG_ERROR);
		}
		close(fd[FD_IN]);
		fd[FD_IN] = fd_pipe[FD_IN];
		close(fd_pipe[FD_OUT]);
		i ++;
	}
	close(fd_pipe[FD_IN]);
	close(fd[FD_OUT]);
	waitpid(-1, NULL, 0);
	free(pids);
	return (0);
}

void	here_doc(char *limiter, int argc)
{
	int		pid;
	int		fd[2];
	char	*line;

	if (argc < 6)
	{
		ft_putstr_fd(WRONG_ARG_NUM, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
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
		close(fd[0]);
		while (true)
        {
            line = get_next_line(STDIN_FILENO);
            if (line == NULL)
            {
                perror("Error reading from standard input");
                exit(EXIT_FAILURE);
            }
            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
            {
                free(line);
                break;
            }
            write(fd[1], line, ft_strlen(line));
            free(line);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
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
		return(NEG_ERROR);
	}
	return (fd);
}

int	main(int ac, char **av, char **envp)
{
	int			fd_files[2];
	t_command	*command_list;
	int			exec_pipe_result;

	if (ac < 5 || !av || !av[1])
		return (ft_putstr_fd(WRONG_ARG_NUM, STDERR_FILENO), EXIT_FAILURE);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		fd_files[FD_OUT] = open_file(ac, av, HERE_DOC);
		here_doc(av[2], ac);
		fd_files[FD_IN] = STDIN_FILENO;
		ac --;
		av ++;
	}
	else
	{
		fd_files[FD_OUT] = open_file(ac, av, OUTPUT_FILE);
		fd_files[FD_IN] = open_file(ac, av, INPUT_FILE);
	}
	if (fd_files[FD_OUT] < 0)
		return (EXIT_FAILURE);
	if (fd_files[FD_IN] < 0)
		fd_files[FD_IN] = open("/dev/null", O_RDONLY);
	command_list = build_command_list(ac, av, envp);
	if (!command_list)
		return (close_both_ends(fd_files, !PRINT_PIPE_ERROR), EXIT_FAILURE);
	exec_pipe_result = exec_pipe(command_list, fd_files, ac - 3, envp);
	free_command_list(command_list, ac - 3);
	close(fd_files[FD_OUT]);
    close(fd_files[FD_IN]);
	if (exec_pipe_result == NEG_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
