/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:36:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 15:16:34 by yioffe           ###   ########.fr       */
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

