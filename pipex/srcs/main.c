/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/25 14:44:27 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int ac, char **av) 
{
    char	*file1;
	char	*cmd1;
	char	*cmd2;
	char	*file2;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac < 5)
	{
        ft_putstr_fd(LESS_ARGS, 2);
        return (1);
    }

    file1 = av[1];
    cmd1 = av[2];
    cmd2 = av[3];
    file2 = av[ac - 1];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork first child
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    }

    if (pid1 == 0) {
        // Child 1
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close pipe write end

        // Execute cmd1
        execlp(cmd1, cmd1, file1, NULL);
        perror("execlp cmd1");
        return 1;
    }

    // Fork second child
	pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    }

    if (pid2 == 0) {
        // Child 2
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]); // Close pipe read end

        // Execute cmd2
        execlp(cmd2, cmd2, file2, NULL);
        perror("execlp cmd2");
        return 1;
    }

    // Parent
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
