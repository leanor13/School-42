/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:09:05 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/20 22:38:52 by yioffe           ###   ########.fr       */
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

int	my_zoom(int button, int x, int y, t_fractal *f)
{
	double	coeff;
	double	scale_factor;
	double	range_avg;

	range_avg = (f->max_bound.x - f->min_bound.x) + (f->max_bound.y - f->min_bound.y)/2.0;
	(void)x;
	(void)y;
	scale_factor = pow(ZOOM_IN, log10(range_avg + 1) + 1);
	coeff = 0.0;
	if (button == ON_MOUSEDOWN)
		coeff = scale_factor;
	else if (button == ON_MOUSEUP)
		coeff = 1.0 / scale_factor;
	if (coeff != 0.0)
	{	
		f->min_bound.x *= coeff;
		f->min_bound.y *= coeff;
		f->max_bound.x *= coeff;
		f->max_bound.y *= coeff;
		draw_fractal(f);
	}
	return (0);
}

int	my_move(int keycode, t_fractal *f)
{
	t_point	move_point;
	double	scale_factor;
	double	range_avg;

	range_avg = (f->max_bound.x - f->min_bound.x + f->max_bound.y - f->min_bound.y) / 2.0;
	scale_factor = log10(range_avg + 1) + 1;
	if (keycode == UP)
		move_point = (t_point){0.0, scale_factor * MOVE_STEP};
	else if (keycode == DOWN)
		move_point = (t_point){0.0, -scale_factor * MOVE_STEP};
	else if (keycode == RIGHT)
		move_point = (t_point){scale_factor * MOVE_STEP, 0.0};
	else if (keycode == LEFT)
		move_point = (t_point){-scale_factor * MOVE_STEP, 0.0};
	if (move_point.x != 0.0 || move_point.y != 0.0)
	{
		f->min_bound.x += move_point.x;
		f->min_bound.y += move_point.y;
		f->max_bound.x += move_point.x;
		f->max_bound.y += move_point.y;
		draw_fractal(f);
	}
	return (0);
}

t_fractal	*init_fractal(t_pixel pix_max,  t_point min_bound, t_point max_bound, int iter)
{
	t_data		img;
	t_vars		vars;
	t_fractal	*result;

	result = malloc(sizeof(t_fractal));
	if (!result)
	{
		perror("Error allocating memory for fractal");
		exit(EXIT_FAILURE);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, pix_max.x, pix_max.y, "Fract-ol!");
	img.img = mlx_new_image(vars.mlx, pix_max.x, pix_max.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	result->min_bound = min_bound;
	result->max_bound = max_bound;
	result->pix_max = pix_max;
	result->iter = iter;
	result->img = img;
	result->vars = vars;
	return (result);
}

void	draw_fractal(t_fractal *f)
{
	color_all_pixels(&f->img, f->min_bound, f->max_bound, f->pix_max, f->iter);
	mlx_put_image_to_window(f->vars.mlx, f->vars.win, f->img.img, 0, 0);
}

int	main(void)
{
	t_pixel		pix_max = { 500, 500 };
	t_point		min_bound = {-2, -2};
	t_point		max_bound = {2, 2};
	int			max_iter = 100;
	t_fractal	*f;

	f = init_fractal(pix_max, min_bound, max_bound, max_iter);
	if (!f) {
		fprintf(stderr, "Error: Failed to initialize fractal\n");
		return (1);
	}

	if (!f->vars.win) {
		fprintf(stderr, "Error: Window pointer is NULL\n");
		return (1);
	}
	mlx_mouse_hook(f->vars.win, my_zoom, f);
	mlx_key_hook(f->vars.win, my_move, f);
	mlx_hook(f->vars.win, 17, 131072, close_win2, &f->vars);
	mlx_hook(f->vars.win, 2, 1L<<0, close_win, &f->vars);
	draw_fractal(f);
	mlx_loop(f->vars.mlx);
	//mlx_destroy_window(vars.mlx, vars.win);
	//mlx_destroy_display(vars.mlx);
	return (0);
}
