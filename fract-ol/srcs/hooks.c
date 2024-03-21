/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:12:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 15:53:13 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	close_win(int keycode, t_fractal *f)
{
	if (keycode == ESC)
	{
		f_free(&f);
		exit (EXIT_SUCCESS);
	}
	return (0);
}

int	close_win2(int keycode, t_fractal *f)
{
	(void)keycode;
	f_free(&f);
	exit (EXIT_SUCCESS);
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