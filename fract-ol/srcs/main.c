/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 15:52:15 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	main(void)
{
	t_pixel		pix_max = { 500, 500 };
	t_point		min_bound = {-2, -2};
	t_point		max_bound = {2, 2};
	int			max_iter = 100;
	t_fractal	*f;

	f = init_fractal(pix_max, min_bound, max_bound, max_iter);
	mlx_mouse_hook(f->win, my_zoom, f);
	mlx_key_hook(f->win, my_move, f);
	mlx_hook(f->win, 17, 131072, close_win2, f);
	mlx_hook(f->win, 2, 1L<<0, close_win, f);
	draw_fractal(f);
	mlx_loop(f->mlx);
	return (0);
}
