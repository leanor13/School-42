/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:12:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/26 18:57:35 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	close_win(int keycode, t_fractal *f)
{
	if(keycode == ESC)
	{
		ft_putstr_fd("Window closed with ESC\n", STDOUT_FILENO);
		f_free(&f, NO_ERROR);
	}
	return (0);
}

int	close_win2(t_fractal *f)
{
	ft_putstr_fd("Window closed with cross\n", STDOUT_FILENO);
	f_free(&f, NO_ERROR);
	return (0);
}

int	my_zoom(int button, int x, int y, t_fractal *f)
{
	double	coeff;
	double	scale_factor;
	double	range_avg;
	t_point	mouse;

	range_avg = (f->max_bound.x - f->min_bound.x)
		+ (f->max_bound.y - f->min_bound.y) / 2.0;
	mouse = my_map_pixel((t_pixel){x, y}, f->min_bound, f->max_bound, f->pix_max);
	scale_factor = pow(ZOOM_IN, log10(range_avg + 1) + 1);
	coeff = 0.0;
	if (button == ON_MOUSEDOWN)
		coeff = scale_factor;
	else if (button == ON_MOUSEUP)
		coeff = 1.0 / scale_factor;
	if (coeff != 0.0)
	{
		f->min_bound.x = (f->min_bound.x - mouse.x) * coeff + mouse.x;
    	f->min_bound.y = (f->min_bound.y - mouse.y) * coeff + mouse.y;
    	f->max_bound.x = (f->max_bound.x - mouse.x) * coeff + mouse.x;
    	f->max_bound.y = (f->max_bound.y - mouse.y) * coeff + mouse.y;
		draw_fractal(f);
	}
	return (0);
}

void	change_julia(int keycode, t_fractal *f)
{
	if (keycode == KEY_I)
	{
		if (f->c.y < MAX_JULIA)
			f->c.y += 0.01;
		else
			f->c.y = MIN_JULIA;
	}
	if (keycode == KEY_R)
	{
		if (f->c.x < MAX_JULIA)
			f->c.x += 0.01;
		else
			f->c.x = MIN_JULIA;
	}
}

int	key_press(int keycode, t_fractal *f)
{
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		my_move(keycode, f);
	if (keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3)
		my_color(keycode, f);
	if ((keycode == KEY_I || keycode == KEY_R) && f->color_pix_fun == julia_color_pix)
		change_julia(keycode, f);
	draw_fractal(f);
	return (0);
}

void	my_color(int keycode, t_fractal *f)
{
	if (keycode == KEY_1)
		f->color_scheme = map_color_maxiter;
	if (keycode == KEY_2)
		f->color_scheme = map_color_striped;
	if (keycode == KEY_3)
		f->color_scheme = map_color_b_w;
}

void	my_move(int keycode, t_fractal *f)
{
	t_point	move_point;
	double	range_avg;

	range_avg = (f->max_bound.x - f->min_bound.x
			+ f->max_bound.y - f->min_bound.y) / 20.0;
	move_point = (t_point){0.0, 0.0};
	if (keycode == UP)
		move_point = (t_point){0.0, -range_avg};
	else if (keycode == DOWN)
		move_point = (t_point){0.0, range_avg};
	else if (keycode == RIGHT)
		move_point = (t_point){range_avg, 0.0};
	else if (keycode == LEFT)
		move_point = (t_point){-range_avg, 0.0};
	if (move_point.x != 0.0 || move_point.y != 0.0)
	{
		f->min_bound.x += move_point.x;
		f->min_bound.y += move_point.y;
		f->max_bound.x += move_point.x;
		f->max_bound.y += move_point.y;
	}
}
