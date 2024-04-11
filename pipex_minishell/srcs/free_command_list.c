/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:09:17 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/11 11:01:46 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	close_all_protected();
	command_list = NULL;
}

void	dup_close(int fd, int reference)
{
	if (fd != reference)
	{
		dup2(fd, reference);
		ft_close(fd);
	}
}

