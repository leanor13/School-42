/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:36:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/21 15:55:28 by yioffe           ###   ########.fr       */
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
	t_fractal	*f;

	f = malloc(sizeof(t_fractal));
	if (!f)
	{
		perror("Error allocating memory for fractal");
		exit(EXIT_FAILURE);
	}
	f->mlx = mlx_init();
	if (!f->mlx)
	{
		perror("Error initializing graphics");
		f_free(&f);
		exit(EXIT_FAILURE);
	}
	f->win = mlx_new_window(f->mlx, pix_max.x, pix_max.y, "Fract-ol!");
	if (!f->win)
	{
		perror("Error initializing window");
		f_free(&f);
		exit(EXIT_FAILURE);
	}
	f->img = malloc(sizeof(t_data));
	if (!f->img) 
	{
		perror("Error allocating memory for t_data");
		f_free(&f);
		exit(EXIT_FAILURE);
	}
	f->img->img = mlx_new_image(f->mlx, pix_max.x, pix_max.y);
	if (!f->img->img)
	{
		perror("Error creating image");
		f_free(&f);
		exit(EXIT_FAILURE);
	}
	f->img->addr = mlx_get_data_addr(f->img->img, &f->img->bits_per_pixel, 
		&f->img->line_length, &f->img->endian);
	if (!f->img->addr)
	{
		perror("Error getting image address");
		f_free(&f);
		exit(EXIT_FAILURE);
	}
	f->min_bound = min_bound;
	f->max_bound = max_bound;
	f->pix_max = pix_max;
	f->iter = iter;
	return (f);
}

void	draw_fractal(t_fractal *f)
{
	color_all_pixels(f->img, f->min_bound, f->max_bound, f->pix_max, f->iter);
	mlx_put_image_to_window(f->mlx, f->win, f->img->img, 0, 0);
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

