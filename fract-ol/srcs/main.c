/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 17:19:11 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	main(void)
{
	t_fractal	*f;

	f = init_fractal();
	mlx_mouse_hook(f->win, my_zoom, f);
	mlx_key_hook(f->win, my_move, f);
	mlx_hook(f->win, 17, 131072, &close_win2, f);
	mlx_hook(f->win, 2, 1L<<0, &close_win, f);
	draw_fractal(f);
	mlx_loop(f->mlx);
	return (0);
}
