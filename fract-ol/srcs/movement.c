/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:25:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 18:27:20 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	is_square(t_point min_bound, t_point max_bound)
{
	double	width;
	double	height;

	width = max_bound.x - min_bound.x;
	height = max_bound.y - min_bound.y;
	return (fabs(width - height) <= DBL_MIN); 
}

static void	make_square(t_point *min_bound, t_point *max_bound)
{
	double	width;
	double	height;
	double	center;

	width = max_bound->x - min_bound->x;
	height = max_bound->y - min_bound->y;
	if (width > height)
	{
		center = (max_bound->y + min_bound->y) / 2.0;
		min_bound->y = center - width / 2.0;
		max_bound->y = center + width / 2.0;
	}
	else if (height > width)
	{
		center = (max_bound->x + min_bound->x) / 2.0;
		min_bound->x = center - height / 2.0;
		max_bound->x = center + height / 2.0;
	}
}

double	zoom_coeff(double scale_factor, int button)
{
	double	coeff;

	coeff = 0;
	if (button == ON_MOUSEDOWN)
		coeff = scale_factor;
	else if (button == ON_MOUSEUP)
		coeff = 1.0 / scale_factor;
	return (coeff);
}

int	my_zoom(int button, int x, int y, t_fractal *f)
{
	double	coeff;
	double	scale_factor;
	double	range_avg;
	t_point	mouse;

	range_avg = (f->max_bound.x - f->min_bound.x) + (f->max_bound.y
			- f->min_bound.y) / 2.0;
	mouse = my_map_pixel((t_pixel){x, y}, f->min_bound, f->max_bound,
			f->pix_max);
	scale_factor = pow(ZOOM_IN, log10(range_avg + 1) + 1);
	coeff = zoom_coeff(scale_factor, button);
	if (coeff != 0.0)
	{
		f->min_bound.x = (f->min_bound.x - mouse.x) * coeff + mouse.x;
		f->min_bound.y = (f->min_bound.y - mouse.y) * coeff + mouse.y;
		f->max_bound.x = (f->max_bound.x - mouse.x) * coeff + mouse.x;
		f->max_bound.y = (f->max_bound.y - mouse.y) * coeff + mouse.y;
		if (!is_square(f->min_bound, f->max_bound))
			make_square(&f->min_bound, &f->max_bound);
		draw_fractal(f);
	}
	return (0);
}

void	my_move(int keycode, t_fractal *f)
{
	t_point	move_point;
	double	range_avg;

	range_avg = (f->max_bound.x - f->min_bound.x + f->max_bound.y
			- f->min_bound.y) / 20.0;
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
