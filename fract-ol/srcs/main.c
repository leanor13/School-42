/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 12:54:57 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	activate_hooks(t_fractal *f)
{
	mlx_mouse_hook(f->win, my_zoom, f);
	mlx_key_hook(f->win, key_press, f);
	mlx_hook(f->win, 17, 0, &close_win, f);
	//mlx_hook(f->win, 2, 1L << 0, &close_win, f);
	mlx_hook(f->win, 2, 1L << 1, &key_hold, f);
}

int	main(int ac, char **av)
{
	t_fractal	*f;

	f = handle_input_and_init(ac, av);
	activate_hooks(f);
	draw_fractal(f);
	mlx_loop(f->mlx);
	return (0);
}
