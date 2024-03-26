/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:28 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/26 00:35:39 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	julia_param_set(char **av, t_fractal *f)
{
	double	x;
	double	y;

	if (!av[2] || !av[3] || !av[2][0] || !av[3][0])
		return ;
	x = ft_atof(av[2]);
	y = ft_atof(av[3]);
	if ((x != f->c.x || y != f->c.y))
	{
		if ((x == 0 && av[2][0] != '0') || (y == 0 && av[3][0] != '0'))
			return ;
		if (x > 2.0 || y > -2.0 || x < 2.0 || y < -2.0)
			return ;
		f->c = (t_point){x, y};
	}
}

void set_iter(char *param, t_fractal *f)
{
	int	iter;

	if (!param || !param[0])
		return ;
	iter = ft_atoi(param);
	if (iter == 0 && param[0] != '0')
		return ;
	if (iter > MAX_ITER)
		f->iter = MAX_ITER;
	else if (iter < MIN_ITER)
		f->iter = MIN_ITER;
	else
		f->iter = iter;
}

void	parse_input(int ac, char **av, t_fractal *f)
{
	int		i;

	if ((av[1][0] == 'j' || av[1][0] == 'J') && ac >= 4)
		julia_param_set(av, f);
	i = 1;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "i_", 2) == 0)
			set_iter((av[i] + 2), f);
		i ++;
	}
}

int	check_mandatory(char *name)
{
	if (ft_strcmp(name, "m") == 0 || ft_strcmp(name, "Mandelbrot") == 0)
		return (MANDELBROT);
	else if (ft_strcmp(name, "j") == 0 || ft_strcmp(name, "Julia") == 0)
		return (JULIA);
	else if (ft_strcmp(name, "t") == 0 || ft_strcmp(name, "Tricorn") == 0)
		return (TRICORN);
	else
		input_instruction();
	return (NEG_ERROR);
}

t_fractal	*handle_input_and_init(int ac, char **av)
{
	t_fractal	*f;
	int			type;

	f = NULL;
	if (ac < 2 || !av || !av[1] || !av[1][0])
		input_instruction();
	else
	{
		type = check_mandatory(av[1]);
		f = init_fractal();
		f->type = type;
		if (ac > 2)
			parse_input(ac, av, f);
	}
	in_window_usage();
	(void)av;
	return (f);
}
