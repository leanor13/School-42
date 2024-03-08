
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
//#include "../../pipex/includes/libft/libft.h"
int	BUFFER = 80;

int	main(int ac, char **av, char **envp)
{
	char	*command[] = { "grep", "-E", "c$", "-", NULL };
	char	*bin_file = command[0];
	char	command_path[] = "/usr/bin/grep";
	int		fd_in;
	int		fd_out;

	
	if (fork() == 0)
	{
		// child process
		write(STDOUT_FILENO, "child\n", 6);
		//fd_in = open("inp.txt", O_RDONLY);
		fd_out = open("outp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd_out == -1)
		{
			perror("Failed opening output file");
			return(1);
		}
		//dup2(fd_in, STDIN_FILENO);
		//close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		if (execve(command_path, command, envp) == -1)
			write(STDOUT_FILENO, "Error executing grep\n", 22);
	}
	else
	{
		//parent process
		wait(NULL);
		write(STDOUT_FILENO, "parent\n", 7);
		write(STDOUT_FILENO, "done\n", 5);
	}
	//write(STDOUT_FILENO, "hiii\n", 5);
	//write(STDERR_FILENO, "done\n", 5);
}