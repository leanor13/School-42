/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/02 10:08:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int			fd_pipe[0][2];
	int			fd_input;
	int			fd_output;
	int			pid1;
	int			pid2;
	t_command	*command_list;

	
	fd_input = open(av[1], O_RDONLY);
	if (fd_input == -1)
	{
		perror("Failed opening input file");
        return(1);
    }
	fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		perror("Failed opening output file");
        return(1);
    }
	command_list = build_command_list(ac, av, envp);
	if (!command_list)
	{
		close(fd_input);
		close(fd_output);
		return(0);
	}
	
	if (pipe(fd_pipe[0]) == -1)
	{
		perror("Error creating pipe");
		return (EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error forking");
		return (EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(fd_input, STDIN_FILENO);
        dup2(fd_pipe[0][1], STDOUT_FILENO);
		close(fd_input);
		close(fd_pipe[0][0]);
		close(fd_pipe[0][1]);
		if (execve(command_list[0].path, command_list[0].args, envp) == -1) 
		{
			perror("execve");
			free(command_list);
			return (EXIT_FAILURE);
		}
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error forking");
		return (EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(fd_pipe[0][0], STDIN_FILENO);
        dup2(fd_output, STDOUT_FILENO);
		close(fd_pipe[0][0]);
		close(fd_pipe[0][1]);
		close(fd_input);
		close(fd_output);
		if (execve(command_list[1].path, command_list[1].args, envp) == -1) 
		{
			perror("execve");
			free(command_list);
			return (EXIT_FAILURE);
		}
	}
	close(fd_input);
	close(fd_output);
	close(fd_pipe[0][0]);
	close(fd_pipe[0][1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_command_list(command_list, ac - 3);
	return (EXIT_SUCCESS);
}
