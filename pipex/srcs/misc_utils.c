/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:02:16 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/10 13:44:03 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
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
