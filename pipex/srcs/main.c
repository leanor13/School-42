/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/08 16:00:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec_command(t_command *command, int fd_in, int fd_out, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error forking"), NEG_ERROR);
	else if (pid == 0)
	{
		write(2, "I am child\n", 11);
		if (fd_in != STDIN_FILENO)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (fd_out != STDOUT_FILENO)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
		if (execve(command->path, command->args, envp) == -1)
		{
			perror("Execve error");
			exit (NEG_ERROR);
		}
	}
	return (pid);
	// make sure to free command_list in case -1 is returned.
}

static void	close_both_ends(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	exec_pipe(t_command *command_list, int fd_in_out_files[2], int comm_num, char **envp)
{
	int	fd_pipe[2];
	int	fd_in_out[2];
	int	*pids;
	int	i;

	pids = malloc(comm_num * sizeof(int));
	if (!pids)
	{
		close_both_ends(fd_in_out);
		return(perror("Error allocating memory for pids"), NEG_ERROR);
	}
	i = 0;
	fd_in_out[FD_IN] = fd_in_out_files[FD_IN];
	while (i <= comm_num - 1)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Error creating pipe");
			close_both_ends(fd_in_out);
			free(pids);
			return NEG_ERROR;
		}
		if (i == comm_num - 1)
			fd_in_out[FD_OUT] = fd_in_out_files[FD_OUT];
		else
			fd_in_out[FD_OUT] = fd_pipe[FD_OUT];
		pids[i] = exec_command(&command_list[i], fd_in_out[FD_IN], fd_in_out[FD_OUT], envp);
		if (pids[i] == -1)
		{
			close_both_ends(fd_in_out);
			if (i != comm_num - 1)
                close(fd_in_out_files[FD_OUT]);
			free(pids);
			return NEG_ERROR;
		}
		close(fd_in_out[FD_IN]);
		fd_in_out[FD_IN] = fd_pipe[FD_IN];
		i ++;
	}
    i = 0;
    while (i < comm_num)
        waitpid(pids[i++], NULL, 0);
	free (pids);
	return (0);
}

int main(int ac, char **av, char **envp)
{
    int fd_in_out_files[2];
    t_command *command_list;
	int exec_pipe_result;

    fd_in_out_files[FD_IN] = open(av[1], O_RDONLY);
    if (fd_in_out_files[FD_IN] == -1)
        return(perror("Failed opening input file"), EXIT_FAILURE);
    fd_in_out_files[FD_OUT] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_in_out_files[FD_OUT] == -1)
	{
		close(fd_in_out_files[FD_IN]);
        return(perror("Failed opening output file"), EXIT_FAILURE);
	}
    command_list = build_command_list(ac, av, envp);
    if (!command_list)
        return(close_both_ends(fd_in_out_files), EXIT_FAILURE);
	exec_pipe_result = exec_pipe(command_list, fd_in_out_files, ac - 3, envp);
	free_command_list(command_list, ac - 3);
    if (exec_pipe_result == NEG_ERROR)
        return (EXIT_FAILURE);
    return (0);
}
