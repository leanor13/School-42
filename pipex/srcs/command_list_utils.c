/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:48 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/13 14:30:52 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	dir_len_count(char *dir_start, bool is_end)
{
	int	dir_len;

	if (ft_strchr(dir_start, ':') != NULL)
		dir_len = ft_strchr(dir_start, ':') - dir_start;
	else
	{
		is_end = true;
		dir_len = ft_strlen(dir_start);
	}
	return (dir_len);
}

char	*absolute_path(char *command)
{
	if (*command == '/')
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
			return (ft_putstr_fd("Wrong command path\n", STDERR_FILENO), NULL);
	}
	return (NULL);
}
