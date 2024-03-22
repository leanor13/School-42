/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/22 13:09:26 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	activate_hooks(t_fractal *f)
{
	mlx_mouse_hook(f->win, my_zoom, f);
	mlx_key_hook(f->win, my_move, f);
	mlx_hook(f->win, 17, 0, &close_win2, f);
	mlx_hook(f->win, 2, 1L << 0, &close_win, f);
}

int	main(void)
{
	t_fractal	*f;

	f = init_fractal();
	activate_hooks(f);
	draw_fractal(f);
	mlx_loop(f->mlx);
	return (0);
}
