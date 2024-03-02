/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:02:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/02 10:05:25 by yioffe           ###   ########.fr       */
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
	char	*dir_start;

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
				command_path_buf = make_path(command, dir_len, dir_start,
						false);
				if (command_path_buf)
					return (command_path_buf);
				dir_start = ft_strchr(dir_start, ':') + 1;
			}
		}
		envp++;
	}
	return (NULL);
}

void	new_command(t_command *command, char *av_curr, char **envp)
{
	command->command = av_curr[0];
	command->args = ft_split_pipex(av_curr, ' ');
	if (!command->args)
		return ;
	command->path = find_path(command->command, envp);
	if (!command->path)
	{
		free(command->args);
		command->args = NULL;
		return ;
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
		return (perror(WRONG_ARG_NUM), NULL);
	command_list = calloc((ac - 3), sizeof(t_command));
	if (!command_list)
		return (perror("Could not allocate command list"), NULL);
	i = 2;
	while (i < ac - 1)
	{
		new_command(&command_list[i - 2], av[i], envp);
		if (!command_list[i - 2].args || !command_list[i - 2].path)
		{
			free_command_list(command_list, i - 2);
			return (NULL);
		}
		i++;
	}
	return (command_list);
}

void	free_command_list(t_command *command_list, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (command_list[i].args[j])
		{
			free(command_list[i].args[j]);
			command_list[i].args[j] = NULL;
			j++;
		}
		free(command_list[i].args);
		command_list[i].args = NULL;
		free(command_list[i].path);
		command_list[i].path = NULL;
		i++;
	}
	free(command_list);
	command_list = NULL;
}
