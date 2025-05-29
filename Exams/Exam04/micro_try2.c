#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void ft_close_protected(void)
{
	int i = 3;

	while (i < 1024)
	{
		close(i);
		i ++;
	}
}

int	parse_command(char **av)
{
	int i = 0;

	if (!av || !av[0])
		return (0);
	while (av[i] && strcmp(";", av[i]) != 0 && strcmp("|", av[i]) != 0)
		i ++;
	return i;
}

void	print_error(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}

void	handle_cd(char **av)
{
	if (av[1] == NULL || av[2] != NULL)
		print_error("error: cd: bad arguments", NULL);
	else if (chdir(av[1]) != 0)
		print_error("error: cd: cannot change directory to path_to_change ", av[1]);
}

void	exec_command(char **av, int i, int temp_fdin, char **env)
{
	if (av[i])
		av[i] = NULL;
	dup2(temp_fdin, STDIN_FILENO);
	close(temp_fdin);
	execve(av[0], av, env);
	print_error("error: cannot execute executable_that_failed ", av[1]);
	exit(EXIT_FAILURE);
}

void	handle_single_command(char **av, int i, int *temp_fdin, char **env)
{
	if (fork() == 0)
	{
		exec_command(av, i, *temp_fdin, env);
	}
	else
	{
		close(*temp_fdin);
		while (waitpid(-1, NULL, WUNTRACED) != -1);
		*temp_fdin = dup(STDIN_FILENO);
	}
}

void	handle_pipe(char **av, int i, int *temp_fdin, int fd[2], char **env)
{
	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		exec_command(av, i, *temp_fdin, env);
	}
	else
	{
		close(fd[1]);
		close(*temp_fdin);
		*temp_fdin = fd[0];
	}
}

int	main(int ac, char **av, char **env)
{
	int i = 0;
	int fd[2];
	int temp_fdin;

	temp_fdin = dup(STDIN_FILENO);
	(void) ac;

	while (av[i] && av[i+1])
	{
		av = &av[i+1];
		i = parse_command(av);
		if (i == 0)
			continue;
		
		if (strcmp(av[0], "cd") == 0)
			handle_cd(av);
		else if (av[i] == NULL || strcmp(";", av[i]) == 0)
			handle_single_command(av, i, &temp_fdin, env);
		else if (strcmp(av[i], "|") == 0)
			handle_pipe(av, i, &temp_fdin, fd, env);
	}
	ft_close_protected();
	return(0);
}