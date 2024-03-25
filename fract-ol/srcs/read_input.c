/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:28 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/25 13:19:04 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	parse_input(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	check_mandatory(char *name)
{
	if (ft_strcmp(name, "m") == 0 || ft_strcmp(name, "Mandelbrot") == 0)
		return ;
	else if (ft_strcmp(name, "j") == 0 || ft_strcmp(name, "Julia") == 0)
		return ;
	else if (ft_strcmp(name, "t") == 0 || ft_strcmp(name, "Tricorn") == 0)
		return ;
	else
		input_instruction();
}

t_fractal	*handle_input_and_init(int ac, char **av)
{
	t_fractal	*f;

	f = NULL;
	if (ac < 2 || !av || !av[1] || !av[1][0])
		input_instruction();
	else
	{
		check_mandatory(av[1]);
		f = init_fractal();
		parse_input(ac, av);
	}
	in_window_usage();
	(void)av;
	return (f);
}
