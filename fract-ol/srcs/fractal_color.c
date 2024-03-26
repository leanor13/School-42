/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:23 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/26 01:30:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	color_pixel(t_fractal *f, t_pixel pixel)
{
	int			i;
	t_point		curr;
	t_point		c_0;
	int			color;
	double		c2;

	i = 0;
	curr = my_map_pixel(pixel, f->min_bound, f->max_bound, f->pix_max);
	c2 = curr.x * curr.x + curr.y * curr.y;
	if (f->type == MANDELBROT)
	{
		if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * curr.x - 3.0 < 0.0) 
			return (f->color_scheme(f->iter, f->iter));
		if (16.0 * (c2 + 2.0 * curr.x + 1.0) - 1.0 < 0.0) 
			return (f->color_scheme(f->iter, f->iter));
		c_0 = curr;
	}
	else if (f->type == JULIA)
		c_0 = f->c;
	else if (f->type == TRICORN)
		c_0 = curr;
	while (i < f->iter)
	{
		if ((curr.y * curr.y + curr.x * curr.x >= 4))
			break ;
		if (f->type == MANDELBROT || f->type == JULIA)
			curr = mandelbrot_iter(curr, c_0);
		else if (f->type == TRICORN)
			curr = tricorn_iter(curr, c_0);
		i ++;
	}
	color = f->color_scheme(i, f->iter);
	return (color);
}
