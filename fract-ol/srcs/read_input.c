/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:28 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 11:48:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	validate_input(int ac, char **av)
{
	if (ac < 2)
		input_instruction();
	else
		in_window_usage();
	(void)av;
	return;
}
