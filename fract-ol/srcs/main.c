/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/19 16:30:17 by yioffe           ###   ########.fr       */
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
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

int	close_win2(int keycode, t_vars *vars)
{
	(void)keycode;
	if (!vars || !vars->mlx || !vars->win)
		return (0);
	else
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

int	my_zoom(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	if (button == 4)
	{
		printf("Here\n");
	}
	return (0);
}

int	main(void)
{
	t_data	img;
	int		img_height = 500;
	int		img_width = 500;
	t_pixel	pix_max = { img_height, img_width };
	t_point	min_bound = {-2, -2};
	t_point	max_bound = {2, 2};
	int		max_iter = 100;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, pix_max.x, pix_max.y, "Fract-ol!");
	img.img = mlx_new_image(vars.mlx, pix_max.x, pix_max.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color_all_pixels(&img, min_bound, max_bound, pix_max, max_iter);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//int (*f)(int button, int x, int y, void *param)
	mlx_mouse_hook(vars.win, my_zoom, &vars);
	mlx_hook(vars.win, 17, 1, close_win2, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	//mlx_hook(vars.win, 17, 0, close_win2, &vars);
	mlx_loop(vars.mlx);
	//mlx_destroy_window(vars.mlx, vars.win);
	//mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (0);
}
