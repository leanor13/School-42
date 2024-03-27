/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:17:57 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/27 12:00:52 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static t_point	mandelbrot_iter(t_point c, t_point c_0)
{
	t_point	next;

	next.x = c.x * c.x - c.y * c.y + c_0.x;
	next.y = 2 * c.x * c.y + c_0.y;
	return (next);
}

int	mandelbrot_color_pix(t_fractal *f, t_pixel pixel)
{
	int		i;
	t_point	curr;
	t_point	c_0;
	double	c2;
	t_point	next;

	i = 0;
	(void)next;
	curr = my_map_pixel(pixel, f->min_bound, f->max_bound, f->pix_max);
	c2 = curr.x * curr.x + curr.y * curr.y;
	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * curr.x - 3.0 < 0.0)
		return (f->color_scheme(f->iter, f->iter));
	if (16.0 * (c2 + 2.0 * curr.x + 1.0) - 1.0 < 0.0)
		return (f->color_scheme(f->iter, f->iter));
	c_0 = curr;
	while (i < f->iter)
	{
		if ((curr.y * curr.y + curr.x * curr.x >= 4))
			break ;
		curr = mandelbrot_iter(curr, c_0);
		i++;
	}
	return (f->color_scheme(i, f->iter));
}

int	julia_color_pix(t_fractal *f, t_pixel pixel)
{
	int		i;
	t_point	curr;
	t_point	c_0;
	int		color;
	t_point	next;

	i = 0;
	curr = my_map_pixel(pixel, f->min_bound, f->max_bound, f->pix_max);
	c_0 = f->c;
	while (i < f->iter)
	{
		if (curr.x * curr.x + curr.y * curr.y >= 4)
			break ;
		next.x = curr.x * curr.x - curr.y * curr.y + c_0.x;
		next.y = 2 * curr.x * curr.y + c_0.y;
		curr = next;
		i++;
	}
	color = f->color_scheme(i, f->iter);
	return (color);
}

int	tricorn_color_pix(t_fractal *f, t_pixel pixel)
{
	int		i;
	t_point	curr;
	t_point	c_0;
	int		color;
	t_point	next;

	i = 0;
	curr = my_map_pixel(pixel, f->min_bound, f->max_bound, f->pix_max);
	c_0 = curr;
	while (i < f->iter)
	{
		if (curr.x * curr.x + curr.y * curr.y >= 4)
			break ;
		next.x = curr.x * curr.x - curr.y * curr.y + c_0.x;
		next.y = -2 * curr.x * curr.y + c_0.y;
		curr = next;
		i++;
	}
	color = f->color_scheme(i, f->iter);
	return (color);
}

