/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:13:50 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/17 16:23:50 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_current_pwd(void)
{
	char	*buffer;

	buffer = (char *)calloc(PATH_MAX, sizeof(char));
	if (buffer != NULL)
	{
		if (getcwd(buffer, PATH_MAX) == NULL)
		{
			perror("getcwd() error");
			free(buffer);
			return (NULL);
		}
	}
	else
		perror("calloc() error");
	return (buffer);
}
