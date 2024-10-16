/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:15:17 by shackbei          #+#    #+#             */
/*   Updated: 2024/10/05 11:13:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}

void ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
	//overwrite ; or | or NULL with NULL to use the array as input for execve.
	//we are here in the child so it has no impact in the parent process.
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, env);
	ft_putstr_fd2("error: cannot execute ", argv[0]);
	exit(1);
}

int parse_command(char *argv[])
{
	int i = 0;
	while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
		i++;
	return i;
}

void handle_cd(char *argv[])
{
	if (strcmp(argv[0], "cd") == 0)
	{
		if (argv[2] != NULL && strcmp(argv[2], "|") != 0 && strcmp(argv[2], ";") != 0)
			ft_putstr_fd2("error: cd: bad arguments", NULL);
		else if (chdir(argv[1]) != 0)
			ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
	}
}

void execute_in_stdout(char *argv[], int i, int *tmp_fd, char *env[])
{
	if (fork() == 0)
		ft_execute(argv, i, *tmp_fd, env);
	else
	{
		close(*tmp_fd);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		*tmp_fd = dup(STDIN_FILENO);
	}
}

void handle_pipe(char *argv[], int i, int *tmp_fd, int fd[2], char *env[])
{
	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execute(argv, i, *tmp_fd, env);
	}
	else
	{
		close(fd[1]);
		close(*tmp_fd);
		*tmp_fd = fd[0];
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int fd[2];
	int tmp_fd;

	(void)argc;
	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = parse_command(argv);
		if (strcmp(argv[0], "cd") == 0)
			handle_cd(argv);
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
			execute_in_stdout(argv, i, &tmp_fd, env);
		else if (i != 0 && strcmp(argv[i], "|") == 0)
			handle_pipe(argv, i, &tmp_fd, fd, env);
	}
	close(tmp_fd);
	return (0);
}
