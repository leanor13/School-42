/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:36:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/18 22:26:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, t_pixel pixel, int color)
{
	char	*dst;

	dst = data->addr + (pixel.y * data->line_length + pixel.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_complex	my_map_pixel(t_pixel pixel, t_point min_bound, t_point max_bound, t_pixel pix_max)
{
	t_complex	result;
	double		x_range;
	double		y_range;
	
	x_range = (max_bound.x - min_bound.x) / pix_max.x;
	y_range = (max_bound.y - min_bound.y) / pix_max.y;
	result.real = pixel.x * x_range + min_bound.x;
	result.imaginary = pixel.y * y_range + min_bound.y;
	return (result);
}

void	color_pixel(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, t_pixel pixel, int max_iter)
{
	int			i;
	t_complex	curr;
	t_complex	c_0;
	int			color;

	i = 0;
	curr = my_map_pixel(pixel, min_bound, max_bound, pix_max);
	c_0 = curr;
	while (i < max_iter)
	{
		if ((curr.imaginary * curr.imaginary + curr.real * curr.real >= 4))
			break ;
		curr = mandelbrot_iter(curr, c_0);
		i ++;
	}
	//color = map_color_general(i);
	color = map_color_maxiter(i, max_iter);
	my_mlx_pixel_put(img, pixel, color);
}

void	color_all_pixels(t_data *img, t_point min_bound, t_point max_bound, 
	t_pixel pix_max, int max_iter)
{
	t_pixel	p;

	p = (t_pixel){0, 0};
	while (p.x < pix_max.x)
	{
		p.y = 0;
		while (p.y < pix_max.y)
		{
			color_pixel(img, min_bound, max_bound, pix_max, p, max_iter);
			p.y ++;
		}
		p.x ++;
	}
}