#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>


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
	if (!av[1] || (av[2] && strcmp(";", av[2]) != 0 && strcmp("|", av[2]) != 0))
		print_error("error: cd: bad arguments", NULL);
	else if (chdir(av[1]) != 0)
		print_error("error: cd: cannot change directory to path_to_change", av[1]);
}

void	ft_execute(char **av, int i, int tmp_fdin, char **env)
{
	av[i] = NULL;
	dup2(tmp_fdin, STDIN_FILENO);
	close(tmp_fdin);
	execve(av[0], av, env);

	print_error("error: cannot execute", av[0]);
	exit(1);
}

void	handle_single_command(char **av, int i, int *tmp_fdin, char **env)
{
	if (fork() == 0)
		ft_execute(av, i, *tmp_fdin, env);
	else
	{
		close(*tmp_fdin);
		while (waitpid(-1, NULL, WUNTRACED) != -1);
		*tmp_fdin = dup(STDIN_FILENO);
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

int	main(int ac, char **av, char **env)
{
	int	i = 0;
	int	fd[2];
	int	tmp_fd_in;

	(void)ac;
	tmp_fd_in = dup(STDIN_FILENO);

	while (av[i] && av[i+1])
	{
		av = &av[i+1];
		i = parse_command(av);

		if (i == 0)
			continue;

		if (strcmp("cd", av[0]) == 0)
			handle_cd(av);
		else if (av[i] == NULL || strcmp(";", av[i]) == 0)
			handle_single_command(av, i, &tmp_fd_in, env);
		else if (strcmp("|", av[i]) == 0)
			handle_pipe(av, i, &tmp_fd_in, fd, env); 
	}

	close(tmp_fd_in);
	return (0);
}