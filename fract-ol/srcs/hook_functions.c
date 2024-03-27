/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:12:04 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 12:10:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	close_win(int keycode, t_fractal *f)
{
	if (keycode == ESC)
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

static void	change_julia(int keycode, t_fractal *f)
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

static void	my_color(int keycode, t_fractal *f)
{
	if (keycode == KEY_1)
		f->color_scheme = map_color_maxiter;
	if (keycode == KEY_2)
		f->color_scheme = map_color_striped;
	if (keycode == KEY_3)
		f->color_scheme = map_color_b_w;
}

int	key_press(int keycode, t_fractal *f)
{
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		my_move(keycode, f);
	if (keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3)
		my_color(keycode, f);
	if ((keycode == KEY_I || keycode == KEY_R)
		&& f->color_pix_fun == julia_color_pix)
		change_julia(keycode, f);
	draw_fractal(f);
	return (0);
}
