/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/01 18:54:22 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*make_path(char *command, int dir_len, char *dir_start, bool is_end)
{
	char	*path_buf;
	int		buf_size;
	
	path_buf = ft_calloc((dir_len + ft_strlen(command) + 2), sizeof(char));
	if (!path_buf)
	{
		perror("Failed path buffer memory allocation");
		return (NULL);
	}
	if (is_end)
		buf_size = dir_len + ft_strlen(command) + 2;
	else
		buf_size = dir_len + 1;
	ft_strlcpy(path_buf, dir_start, buf_size);
	ft_strcat(path_buf, "/");
	ft_strcat(path_buf, command);
	if (access(path_buf, X_OK) == 0)
		return (path_buf);
	free(path_buf);
	perror("Failed to find path for command");
	return (NULL);
}

char	*find_path(char *command, char **envp)
{
	char	*command_path_buf;
	int		dir_len;
	char 	*dir_start;

	while (*envp) 
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0) 
		{
			dir_start = *envp + 5;
			while (ft_strchr(dir_start, ':') != NULL || *dir_start != '\0') 
			{
				if (ft_strchr(dir_start, ':') != NULL)
					dir_len = ft_strchr(dir_start, ':') - dir_start;
				else
					dir_len = ft_strlen(dir_start);
				command_path_buf = make_path(command, dir_len, dir_start, false);
				if (command_path_buf)
					return (command_path_buf);
				dir_start = ft_strchr(dir_start, ':') + 1;
			}
		}
		envp ++;
	}
	return (NULL);
}

void	new_command(t_command *command, char *av_curr, char **envp)
{
	command->command = av_curr[0];
	command->args = ft_split_pipex(av_curr, ' ');
	if (!command->args)
        return (NULL);
	command->command_path = find_path(command->command, envp);
	if (!command->command_path)
	{
		free(command->args);
		return(NULL);
	}
	command->fd_input = -1;
	command->fd_output = -1;
}

t_command	*build_command_list(int ac, char **av, char **envp)
{
	int			i;
	t_command	*command_list;
	t_command	*next_command;

	if (ac < 5)
		return (perror("Usage: ./pipex <input_file> <cmd1> <cmd2> <output_file>"), NULL);
	command_list = calloc((ac - 3), sizeof(t_command));
	if (!command_list)
		return (perror("Could not allocate command list"), NULL);
	i = 2;
	while (i < ac - 1)
	{
		new_command(&command_list[i - 2], av[i], envp);
		if (!&command_list[i - 2])
			return(free(command_list), NULL);
		command_list[i - 2] = *next_command;
		free(next_command);
		i ++;
	}
	return (command_list);
}

int	main(int ac, char **av, char **envp)
{
	int		fd_pipe[2];
	int		fd_input;
	int		fd_output;
	int		pid1;
	int		pid2;
	char	*command_path1;
	char	*command1;
	char	*command_path2;
	char	*command2;
	char	**args1;
	char	**args2;
	char	**temp_args1;
	char	**temp_args2;
	t_command	*command_list;

	
	fd_input = open(av[1], O_RDONLY);
	if (fd_input == -1)
	{
		perror("Failed opening input file");
        exit(1);
    }
	fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		perror("Failed opening output file");
        exit(1);
    }
	command_list = build_command_list(ac, av, envp);
	if (!command_list)
	{
		close(fd_input);
		close(fd_output);
		return(0);
	}

	if (command_path1 == NULL || command_path2 == NULL) 
	{
		ft_putstr_fd("Failed: ", 2);
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
        dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_input);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (execve(command_path1, args1, envp) == -1) 
		{
			perror("execve");
			free(command_path1);
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
			return (EXIT_FAILURE);
		}
	}
	close(fd_input);
	close(fd_output);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//ft_putstr_fd(command_path1, 1);
	//ft_putstr_fd(command_path2, 1);
	free(command_path1);
	free(command_path2);
	temp_args1 = args1;
	temp_args2 = args2;
	while (*args1)
	{
		free(*args1);
		args1++;
	}
	while (*args2)
	{
		free(*args2);
		args2++;
	}
	free(temp_args1);
	free(temp_args2);
	return (EXIT_SUCCESS);
}
