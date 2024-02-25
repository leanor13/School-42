
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../includes/pipex.h"

void	call_execve(void)
{
	char *const args[] = {"ls", NULL};
	char *const envp[] = {NULL};

	execve("/bin/ls", args, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	old_main()
{
	pid_t	pid;

	printf("Hello, parent process id here: %d, no fork yet. Pid is constant %d\n", getpid(), pid);
	pid = fork();
	printf("next->fork->next->fork->next->fork->next->fork->next->fork->next->fork\n"); 
	printf("Hello, main process id is %d, pid is now: %d\n", getpid(), pid);
	if (pid < 0)
	{
		printf("fork failed\n");
		return (1);
	}
	else if (pid == 0)
	{
		printf("Hello, I am child process. My pid is %d, my child pid is: %d\n", getpid(), pid);
		call_execve();
	}
	else if (pid > 0)
	{
		printf("Hello, I am parent process. My pid is %d, my child pid is: %d\n", getpid(), pid);
		waitpid(pid, NULL, 0);
		printf("Parent control is back. Pid is%d\n", getpid());
	}
	return (0);
}

int	main()
{
	int		pfd[2];
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork failed\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		ft_putstr_fd("child working\n", 1);
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		ft_putstr_fd("new message\n", 1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("parent working\n", 1);
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		char str[11];
		read(0, str, 11);
		printf("Parent received: %s\n", str);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}