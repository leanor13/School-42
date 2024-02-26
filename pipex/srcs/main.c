/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/02/26 12:38:50 by yioffe           ###   ########.fr       */
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
	//int		fd[2];
	//int		pid1;
	//char 	*args1[] = {"ping", "-c", "5", "google.com", NULL};
	char 	*args2[] = {"ls", "-l", NULL};
	char	*command_path = NULL;
	char	*command;
	
	(void)av;
	(void)ac;
	command = args2[0];
	command_path = find_path(command, envp);
	if (command_path == NULL) {
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" command not found in PATH\n", 2);
		exit(1);
	}

	// Execute the command
	if (execve(command_path, args2, envp) == -1) {
		perror("execve");
		free(command_path);
		exit(1);
	}

	free(command_path);
	return 0;
	/* if (pipe(fd) == -1)
		return 2;
	pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		execve
	}
 */
	return (0);
}
