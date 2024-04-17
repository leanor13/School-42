/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:15:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/17 16:24:02 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **env, char **args, int fd_out)
{
	int		i;

	i = 0;
	if (args && args[0] && args[1])
		return (NEG_ERROR);
	while (env && env[i] != NULL)
	{
		if (*env[i] != '\0' && *env[i] != '=' && ft_strchr(env[i], '='))
			ft_output_nl(env[i], fd_out);
		i ++;
	}
	return (EXIT_SUCCESS);
}
