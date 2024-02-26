/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/26 15:54:19 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *command, char **envp)
{
	int 	i;
	char	*command_path;

	i = 0;
	command_path = 0;
	while (envp[i] != NULL) {
		// Check if the environment variable starts with "PATH="
		if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
			char *path_env = envp[i] + 5; // Skip "PATH="
			char *dir_start = path_env;
			char *dir_end;
			while ((dir_end = ft_strchr(dir_start, ':')) != NULL) 
			{
				// Construct the full path of the command
				char command_path_buf[PATH_MAX];
				int dir_len = dir_end - dir_start;
				ft_strcpy(command_path_buf, dir_start);
				command_path_buf[dir_len] = '\0'; // Null-terminate the string
				ft_strcat(command_path_buf, "/");
				ft_strcat(command_path_buf, command);
				// Check if the command exists and is executable
				if (access(command_path_buf, X_OK) == 0) {
					command_path = ft_strdup(command_path_buf); // Copy the path
					break;
				}
				dir_start = dir_end + 1; // Move to the next directory in PATH
			}
			// Check the last directory in PATH (if it doesn't end with ':')
			if (*dir_start != '\0') 
			{
				char command_path_buf[PATH_MAX];
				ft_strcpy(command_path_buf, dir_start);
				ft_strcat(command_path_buf, "/");
				ft_strcat(command_path_buf, command);
				if (access(command_path_buf, X_OK) == 0) {
					command_path = ft_strdup(command_path_buf); // Copy the path
				}
			}
			break; // Stop searching after finding the command in PATH
		}
		i++; // Move to the next environment variable
	}
	return (command_path);
}

int main(int ac, char **av, char **envp) 
{
	int		fd_pipe[2];
	int		fd_input;
	int		fd_output;
	int		pid1;
	int		pid2;
	char 	*args1[] = {"ping", "-c", "5", "google.com", NULL};
	char 	*args2[] = {"grep", "round-trip", NULL};
	char	*command_path1;
	char	*command1;
	char	*command_path2;
	char	*command2;
	
	(void)av;
	(void)ac;
	fd_input = open(av[1], O_RDONLY);
    if (fd_input == -1) {
        perror("open");
        exit(1);
    }

	fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_output == -1) {
        perror("open");
        exit(1);
    }

	command1 = args1[0];
	command_path1 = find_path(command1, envp);
	command2 = args2[0];
	command_path2 = find_path(command2, envp);
	if (command_path1 == NULL || command_path2 == NULL) 
	{
		ft_putstr_fd("Error: ", 2);
		if (command_path1 == NULL && command_path2 != NULL)
			ft_putstr_fd(command1, 2);
		else if (command_path2 == NULL)
			ft_putstr_fd(command2, 2);
		else
			ft_putstr_fd("for both commands: ", 2);
		ft_putstr_fd(" command not found in PATH\n", 2);
		exit(1);
	}
	if (pipe(fd_pipe) == -1)
	{
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd_input, STDIN_FILENO);
        dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_input);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (execve(command_path1, args1, envp) == -1) 
		{
			perror("execve");
			free(command_path1);
			exit(1);
		}
	}
	pid2 = fork();
	if (pid1 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
        dup2(fd_output, STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		close(fd_input);
		close(fd_output);
		if (execve(command_path2, args2, envp) == -1) 
		{
			perror("execve");
			free(command_path2);
			exit(1);
		}
	}

	close(fd_input);
	close(fd_output);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(command_path1);
	free(command_path2);
	return (0);
}
