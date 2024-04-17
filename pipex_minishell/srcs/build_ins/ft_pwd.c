/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:38:49 by yioffe            #+#    #+#             */
/*   Updated: 2024/04/17 16:14:29 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd_out)
{
	char	*cwd;

	cwd = get_current_pwd();
	if (!cwd)
		return (NEG_ERROR);
	ft_output_nl(cwd, fd_out);
	free(cwd);
	return (EXIT_SUCCESS);
}
