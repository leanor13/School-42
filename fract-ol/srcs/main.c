/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 23:05:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex	mandelbrot_iter(t_complex c, t_complex c_0)
{
	t_complex	next;

	next.real = c.real * c.real - c.imaginary * c.imaginary + c_0.real;
	next.imaginary = 2 * c.real * c.imaginary + c_0.imaginary;
	return (next);
}

int	close_win(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	//void	*mlx;
	//void	*mlx_win;
	t_data	img;
	int		img_height = 500;
	int		img_width = 500;
	t_pixel	pix_max = { img_height, img_width };
	t_point	min_bound = {0.3, 0.3};
	t_point	max_bound = {0.5, 0.5};
	int		max_iter = 100;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, pix_max.x, pix_max.y, "Fract-ol!");
	img.img = mlx_new_image(vars.mlx, pix_max.x, pix_max.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color_all_pixels(&img, min_bound, max_bound, pix_max, max_iter);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx);
}
