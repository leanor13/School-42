/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:02:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/10 13:42:35 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*make_path(char *command, int dir_len, char *dir_start, bool is_end)
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
	return (path_buf);
}

static char	*envp_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp ++;
	}
	return (NULL);
}

static char	*find_path(char *command, char **envp)
{
	char	*command_path_buf;
	int		dir_len;
	char	*dir_start;
	bool	is_end;

	dir_start = envp_path(envp);
	is_end = false;
	while (!is_end)
	{
		if (ft_strchr(dir_start, ':') != NULL)
			dir_len = ft_strchr(dir_start, ':') - dir_start;
		else
		{
			is_end = true;
			dir_len = ft_strlen(dir_start);
		}
		command_path_buf = make_path(command, dir_len, dir_start, is_end);
		if (command_path_buf && access(command_path_buf, X_OK) == 0)
			return (command_path_buf);
		free(command_path_buf);
		if (!is_end)
			dir_start = ft_strchr(dir_start, ':') + 1;
	}
	return (perror("Failed to find path for command"), NULL);
}

static void	new_command(t_command *command, char *av_curr, char **envp)
{
	int	i;

	command->args = ft_split_pipex(av_curr, ' ');
	if (!command->args)
		return ;
	command->command = command->args[0];
	command->path = find_path(command->command, envp);
	if (!command->path)
	{
		i = 0;
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
		command->args = NULL;
		command->command = NULL;
		return ;
	}
}

t_command	*build_command_list(int ac, char **av, char **envp)
{
	int			i;
	t_command	*command_list;

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
